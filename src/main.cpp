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
		double procStartingTime = MPI_Wtime();
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

		std::vector<std::string> array;
		array.push_back("U");
		array.push_back("u");
		array.push_back("D");
		array.push_back("d");
		if (std::find(array.begin(), array.end(), method) == array.end()){
			throw ScaliException::MethodArgument();
		}

		int **slicedMatrix;
		int *sliceSize = new int[2];
		MPI_Status status;
		if(NB_PROCESS == 1){
			Image* img = new Image("../images/"+filename);
			std::cout << "Loading from file" << std::endl;
			img->loadFromFile();

			ScalingAlgorithm* scaling = Utils::chooseAlgorithm(method, img);
			std::cout << "Applying scaling" << std::endl;
			scaling->run(factor);

			std::cout << "Saving from file" << std::endl;
			img->saveInFile(method, factor);
			//img->printMatrix();
		}else{
			if(PROCESS_ID == 0){
				std::cout << "Master" << std::endl;
				//Load image
				Image* img = new Image("../images/"+filename);
				img->loadFromFile();
				img->setSlice(NB_PROCESS);

				//Sending sliced matrixes
				for(int p=1; p < NB_PROCESS; ++p){
					//Assign size values and sending them to procs;
					sliceSize[0] = img->getSliceDimensions(p)[0];
					sliceSize[1] = img->getSliceDimensions(p)[1];
					//sliceSize[2] = img->getSliceSize(p);
					MPI_Send(sliceSize, 2, MPI_INT, p, 0, MPI_COMM_WORLD);

					slicedMatrix = img->getSlice(p);
					MPI_Send(&(slicedMatrix[0][0]), sliceSize[0]*sliceSize[1]*3, MPI_INT, p, 0, MPI_COMM_WORLD);
					//Free the memory up
					free(slicedMatrix[0]);
					free(slicedMatrix);
				}


				slicedMatrix = img->getSlice(0);
				Image* subImage = new Image(sliceSize, slicedMatrix);
				//Scaling part
				ScalingAlgorithm* scaling = Utils::chooseAlgorithm(method, subImage);
				std::cout << "iciciic" << std::endl;
				scaling->run(factor);
				// End Scalling Part
				std::cout << "iciciic" << std::endl;
				slicedMatrix = subImage->getMatrixToSend();
				img->factorSize(Utils::getFactor(method, factor));
				img->resetMatrix();
				std::cout << "icicicici" << std::endl;
				img->updateSlice(0, slicedMatrix);
				std::cout << "okkok" << std::endl;

				free(slicedMatrix[0]);
				free(slicedMatrix);

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
			}else{
				//Receiving size information : width, height, totalSize
				MPI_Recv(sliceSize, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

				slicedMatrix = Utils::initMatrixToSend(sliceSize[0], sliceSize[1]);
				MPI_Recv(&(slicedMatrix[0][0]),  sliceSize[0]*sliceSize[1]*3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

				Image* subImage = new Image(sliceSize, slicedMatrix);

				// Scalling Part
				ScalingAlgorithm* scaling = Utils::chooseAlgorithm(method, subImage);
				std::cout << "ici OKLM ?" << std::endl;
				scaling->run(factor);
				// End Scalling Part

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
