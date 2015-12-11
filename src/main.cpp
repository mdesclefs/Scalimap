#include <iostream>

#include <mpi.h>

#include "ScaliException.h"
#include "Utils.h"

#include "Pixel.h"
#include "Image.h"
#include "ScalingUp.h"
#include "ScalingDown.h"

int main(int argc, char **argv){

	//Pixel* px = new Pixel(125, 125, 125);
	try{
		//Initilisation of MPI
		int PROCESS_ID, NB_PROCESS, len;
		char name[MPI_MAX_PROCESSOR_NAME];

		MPI_Init(&argc, &argv);
		double startingTime, procTime;
		startingTime = MPI_Wtime();
		MPI_Comm_rank(MPI_COMM_WORLD, &PROCESS_ID);
		MPI_Comm_size(MPI_COMM_WORLD, &NB_PROCESS);
		MPI_Get_processor_name(name, &len);

		if(NB_PROCESS == 0){
			throw ScaliException::NullProcessorNumber();
		}

		if(argc != 4){
			throw ScaliException::ArgumentFailure();
		}

		std::string filename;
		std::string method; //Scaling method [Uu](p) [Dd](own)
		int factor; //Scaling factor
		filename = argv[1];
		method = argv[2];
		factor = std::stoi((std::string) argv[3]);

		if(factor <= 1){
			throw ScaliException::NullFactor();
		}

		int* scalingRun = new int[2];
		bool multipleRun = false;
		if(factor != 2 && factor != 3){
			scalingRun = Utils::decomposeFactor(factor);
			multipleRun = true;
		}

		if (!(method == "U" || method == "u" || method == "d" || method == "D")){
			throw ScaliException::MethodArgument();
		}

		int **slicedMatrix;
		int *sliceSize = new int[2];
		double* execution = new double[1];
		MPI_Status status;
		if(NB_PROCESS == 1){
			Image* img = new Image("../images/"+filename);
			std::cout << "One process execution" << std::endl;
			img->loadFromFile();

			ScalingAlgorithm* scaling = Utils::chooseAlgorithm(method, img);
			std::cout << "Applying scaling" << std::endl;

			if(!multipleRun){
				scaling->run(factor);
			}else{
				for(int i=0; i < scalingRun[0]; ++i){
					scaling->run(2);
				}
				for(int i=0; i < scalingRun[1]; ++i){
					scaling->run(3);
				}
			}

			std::cout << "Saving from file" << std::endl;
			img->saveInFile(method, factor);
			//img->printMatrix();
		}else{

			/*
			 * MASTER
			 */
			if(PROCESS_ID == 0){
				//Load image
				Image* img = new Image("../images/"+filename);
				img->loadFromFile();
				img->setSlice(NB_PROCESS);

				//Sending sliced matrixes
				for(int p=1; p < NB_PROCESS; ++p){
					//Assign size values and sending them to procs;
					sliceSize[0] = img->getSliceDimensions(p)[0];
					sliceSize[1] = img->getSliceDimensions(p)[1];
					MPI_Send(sliceSize, 2, MPI_INT, p, 0, MPI_COMM_WORLD);

					slicedMatrix = img->getSlice(p);
					MPI_Send(&(slicedMatrix[0][0]), sliceSize[0]*sliceSize[1]*3, MPI_INT, p, 0, MPI_COMM_WORLD);
					//Free the memory up
					free(slicedMatrix[0]);
					free(slicedMatrix);
				}


				//Init time
				procTime = MPI_Wtime();

				slicedMatrix = img->getSlice(0);
				Image* subImage = new Image(img->getSliceDimensions(0), slicedMatrix);

				//Scaling part
				ScalingAlgorithm* scaling = Utils::chooseAlgorithm(method, subImage);
				if(!multipleRun){
					scaling->run(factor);
				}else{
					for(int i=0; i < scalingRun[0]; ++i){
						scaling->run(2);
					}
					for(int i=0; i < scalingRun[1]; ++i){
						scaling->run(3);
					}
				}
				// End Scalling Part

				//End time
				execution[0] = MPI_Wtime() - procTime;


				slicedMatrix = subImage->getMatrixToSend();
				img->factorSize(Utils::getFactor(method, factor));
				img->resetMatrix();
				img->updateSlice(0, slicedMatrix);

				//Receiving new matrixes
				for(int p=1; p < NB_PROCESS; ++p){
					//Receiving size information : width, height, totalSize
					MPI_Recv(sliceSize, 2, MPI_INT, p, 0, MPI_COMM_WORLD, &status);
					//Receiving resized matrix;
					slicedMatrix = Utils::initMatrixToSend(sliceSize[0], sliceSize[1]);
					MPI_Recv(&(slicedMatrix[0][0]), sliceSize[0]*sliceSize[1]*3, MPI_INT, p, 0, MPI_COMM_WORLD, &status);
					//update matrix
					img->updateSlice(p, slicedMatrix);

					//Free the memory up
					free(slicedMatrix[0]);
					free(slicedMatrix);
				}


				img->saveInFile(method, factor);

				/*
				 * =============== Time Execution
				 */
				std::cout << "Process 1 : " << execution[0] << " sec" << std::endl;

				for(int p=1; p < NB_PROCESS; ++p){
					//Receiving size information : width, height, totalSize
					MPI_Recv(execution, 2, MPI_INT, p, 0, MPI_COMM_WORLD, &status);
					std::cout << "Process " << p+1 << " : " << execution[0] << " sec" << std::endl;
				}
				execution[0] = MPI_Wtime() - startingTime;
				std::cout << "Total time : " << execution[0] << " sec" << std::endl;
				/*
				 * =============== Time Execution
				 */
			}else{
				/*
				 * SLAVE
				 */
				//Receiving size information : width, height, totalSize
				MPI_Recv(sliceSize, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

				slicedMatrix = Utils::initMatrixToSend(sliceSize[0], sliceSize[1]);
				MPI_Recv(&(slicedMatrix[0][0]),  sliceSize[0]*sliceSize[1]*3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

				//Init time
				procTime = MPI_Wtime();

				Image* subImage = new Image(sliceSize, slicedMatrix);

				// Scalling Part
				ScalingAlgorithm* scaling = Utils::chooseAlgorithm(method, subImage);
				if(!multipleRun){
					scaling->run(factor);
				}else{
					for(int i=0; i < scalingRun[0]; ++i){
						scaling->run(2);
					}
					for(int i=0; i < scalingRun[1]; ++i){
						scaling->run(3);
					}
				}

				// End Scalling Part

				//End time
				execution[0] = MPI_Wtime() - procTime;

				//New size and sending them to master;
				sliceSize[0] = subImage->getWidth();
				sliceSize[1] = subImage->getHeight();
				MPI_Send(sliceSize, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);


				//New matrix and sending it to master;
				slicedMatrix = subImage->getMatrixToSend();
				MPI_Send(&(slicedMatrix[0][0]), sliceSize[0]*sliceSize[1]*3, MPI_INT, 0, 0, MPI_COMM_WORLD);

				//Free the memory up
				free(slicedMatrix[0]);
				free(slicedMatrix);

				MPI_Send(execution, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
			}
		}
		MPI_Finalize();
	}
	catch(ScaliException*& e)
	{
		std::cerr << "Error : " << e->what() << std::endl;
	}

	return(0);
}
