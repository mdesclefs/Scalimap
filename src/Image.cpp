/*
 * Image.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "Image.h"
#include "Utils.h"
#include "ScaliException.h"
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

Image::Image(std::string filename) {
	// TODO Auto-generated constructor stub
	_filename = filename;

}

Image::Image(int* sliceSize, int** intMatrix){
	// Usefull for creating a subImage of the initial matrix
	_height = sliceSize[1];
	if(_height <= 0)
		throw ScaliException::SubimageEmpty();
	_width = sliceSize[0];

	//Read matrix
	for(int y=0; y < _height; ++y){
		//Read matrix rows
		std::vector<Pixel*> matrixLine;
		for(int x=0; x < _width; ++x){
			Pixel *px = new Pixel(0,0,0);
			px->setColor(intMatrix[y][(x*3)], intMatrix[y][(x*3)+1], intMatrix[y][(x*3)+2]);
			matrixLine.push_back(px);
		}
		_matrix.push_back(matrixLine);
	}
}

Image::~Image() {
	// TODO Auto-generated destructor stub
}


void Image::loadFromFile(){
	std::string line;
	std::ifstream infile(_filename, std::ios::out|std::ios::binary);

	if (infile.is_open()){
		//Magic Number
		getline (infile,line);
		_magicNumber = line;
		getline (infile,line);

		//Width - Height
		while(line == "" || line.substr(0, 1) == "#") getline (infile,line);
		std::vector<std::string> splittedLine = Utils::split(line, ' ');
		_width = std::stoi(splittedLine[0]);
		_height = std::stoi(splittedLine[1]);
		getline (infile,line);

		//Max color value
		while(line == "" || line.substr(0, 1) == "#") getline (infile,line);
		_maxColorValue = std::stoi(line);
		size_t colorSize = (ceil(log(_maxColorValue) / log(2)) / 8);

		std::string tmpBinary;
		char *ptr = new char[colorSize];
		//Read matrix
		for(int y=0; y < _height; ++y){
			//Read matrix rows
			std::vector<Pixel*> matrixLine;
			for(int x=0; x < _width; ++x){
				Pixel *px = new Pixel(0,0,0);
				int color[3];
				for(int i=0; i < 3; i++){
					//Read first byte
					infile.read(ptr, colorSize);

					//Convert byte in binary
					if(colorSize == 1){
						std::bitset<8> x((*ptr));
						tmpBinary = x.to_string();
					}else{
						std::bitset<16> x((*ptr));
						tmpBinary = x.to_string();
					}

					color[i] = Utils::convertBinaryToDecimal(tmpBinary);
				}
				px->setColor(color[0], color[1], color[2]);
				matrixLine.push_back(px);
			}
			_matrix.push_back(matrixLine);
		}

		infile.close();

	}else{
		std::cout << "The file " << _filename << " couldn't be opened !" << std::endl;
		exit(0);
	}
}

void Image::saveInFile(std::string& method, int factor){

	std::string newFileName = _filename.substr(0, _filename.size()-4);
	newFileName+="_" + method +"_" + std::to_string(factor)+".ppm";

	std::ofstream newfile;
	newfile.open(newFileName,std::ios::out | std::ios::binary);
	newfile << "P6\n";
	newfile	<< (std::to_string(_width)) << " " << (std::to_string(_height)) << "\n";
	newfile	<< (std::to_string(_maxColorValue)) << "\n";

	std::cout << _width << ";" << _height << std::endl;
	for(int y=0; y < _height; ++y){
		for(int x=0; x < _width; ++x){
			//std::cout << x << ";" << y << std::endl;
			newfile.write((char*) &(*(this->getPixel(x, y)))[0], this->getMaxBitsColor());
			newfile.write((char*) &(*(this->getPixel(x, y)))[1], this->getMaxBitsColor());
			newfile.write((char*) &(*(this->getPixel(x, y)))[2], this->getMaxBitsColor());
		}
		newfile << "\n";
	}

	//newfile.write((char*) (this->getMatrixToSend()), _width*_height*3*this->getMaxBitsColor());


	/*size_t size = _width * _height * 3;
	newfile.write((char*) this->getMatrixToSend(), size);*/

	newfile.close();
}

void Image::printMatrix(){
	for(int y=0; y < _height; ++y){
		for(int x=0; x < _width; ++x){
			std::cout << *_matrix[y][x] << "\t\t\t";
		}
		std::cout << std::endl;
	}
}

Pixel*& Image::getPixel(int x, int y){
	if(x < 0)
		x = 0;
	if(x >= _width)
		x = _width-1;
	if(y < 0)
		y = 0;
	if(y >= _height)
		y = _height-1;

	return _matrix[y][x];
}

bool Image::isInMatrix(int x, int y){
	if ((0 <= x && x < _width) && (0 <= y && y < _height)){
		return true;
	}
	return false;
}

void Image::resetMatrix(){
	std::vector<std::vector<Pixel*>> *newMatrix = new std::vector<std::vector<Pixel*>>(_height);
	for ( int i = 0 ; i < _height ; ++i )
	   (*newMatrix)[i].resize(_width);
	this->setMatrix(newMatrix);
}

void Image::setMatrix(std::vector<std::vector<Pixel*>>*& matrix){
	_matrix = *matrix;
}

std::vector<std::vector<Pixel*>> Image::getMatrix(){
	return _matrix;
}

int** Image::getMatrixToSend(){
	int **sliceMatrix = this->initMatrixInRange(0, 0, _width, _height);
	return sliceMatrix;
}

int** Image::initMatrixInRange(int xStart, int yStart, int xOffset, int yOffset){
	xOffset *= 3;
	int *row = (int *)malloc(xOffset*yOffset*sizeof(int));
	int **sliceMatrix = (int **)malloc(yOffset*sizeof(int*));

	std::cout << xStart << "->" << xOffset << std::endl;
	std::cout << yStart << "->" << yOffset << std::endl;

	for (int y=0; y<yOffset; ++y){
		sliceMatrix[y] = &(row[y*xOffset]);
		//We need to add 3 to x on each iteration cause of the 3 colors assignations
		for(int x=0; x<(xOffset/3); ++x){
			Pixel* tmp = getPixel(xStart+x, yStart+y);

			sliceMatrix[y][(x*3)] = (*tmp)[0];
			sliceMatrix[y][(x*3)+1] = (*tmp)[1];
			sliceMatrix[y][(x*3)+2] = (*tmp)[2];
		}
	}

	return sliceMatrix;
}

std::vector<Pixel*> Image::getNeighboor(int x, int y){
	/*
	 * 			(0, -1)
	 * 	(-1,0)	(0,0)	(1, 0)
	 *			(0, 1)
	 */
	std::vector<Pixel*> neighboor;
	std::vector<std::vector<int>> moves;
	moves.push_back(std::vector<int>{-1, -1}); //Square
	moves.push_back(std::vector<int>{0, -1}); //Cross
	moves.push_back(std::vector<int>{1, -1}); //Square

	moves.push_back(std::vector<int>{-1, 0}); //Cross
	moves.push_back(std::vector<int>{1, 0}); //Cross

	moves.push_back(std::vector<int>{-1, 1}); //Square
	moves.push_back(std::vector<int>{0, 1}); //Cross
	moves.push_back(std::vector<int>{1, 1}); //Square

	int newX = 0, newY = 0;
	for(int move=0; move < moves.size(); ++move){
		newX=x + moves[move][0];
		newY=y + moves[move][1];

		if( (0 <= newX && newX < _width) && (0 <= newY && newY < _height) ){
			neighboor.push_back(_matrix[newY][newX]);
		}else{
			neighboor.push_back(_matrix[y][x]);
		}
	}

	return neighboor;
}

void Image::updateSlice(int sliceNumber, int** slice){
	int* position = this->getSlicePosition(sliceNumber);
	int* dimension = this->getSliceDimensions(sliceNumber);

	std::cout << "POSITION = " << position[0] << ";" << position[1] << std::endl;
	std::cout << "DIMENSION = " << dimension[0] << ";" << dimension[1] << std::endl;

	for(int y=0; y<dimension[1]; ++y){
		for(int x=0; x<dimension[0]; ++x){
			//std::cout << "echo" << std::endl;
			Pixel *px = new Pixel(0,0,0);
			px->setColor(slice[y][(x*3)], slice[y][(x*3)+1], slice[y][(x*3)+2]);

			//std::cout << position[1]+y << ";" << position[0]+x << std::endl;
			//delete _matrix[position[1]+y][position[0]+x];
			_matrix[position[1]+y][position[0]+x] = px;
			//std::cout << "on sort ?" << std::endl;
		}
	}
}

void Image::setSlice(int procNbr){

	for(int i=0; i<procNbr; ++i){
		if(i == procNbr-1 && i != 0 && (_widthSlice[0] * procNbr) < _width){
			_widthSlice.push_back((_width / procNbr));
			//Add remaining cells
			_widthSlice[i] += (_width - (_widthSlice[i] * procNbr));
		}else{
			_widthSlice.push_back(_width / procNbr);
		}
	}

	for(int i=0; i<procNbr; ++i){
		_heightSlice.push_back(_height);
		/*
		if(i == procNbr-1 && i != 0 && (_heightSlice[0] * procNbr) < _height){
			_heightSlice.push_back(_height / procNbr);
			//Add remaining cells
			_heightSlice[i] += (_height - (_heightSlice[i] * procNbr));
		}else{
			_heightSlice.push_back(_height / procNbr);
		}
		*/
	}
}

int** Image::getSlice(int sliceNumber){
	std::cout << "Slice : " << sliceNumber << std::endl;
	std::cout << (getSlicePosition(sliceNumber))[0] << "=" << (getSlicePosition(sliceNumber))[1] << "=" << (getSliceDimensions(sliceNumber))[0] << "=" << (getSliceDimensions(sliceNumber))[1] << std::endl;

	int **sliceMatrix = this->initMatrixInRange((getSlicePosition(sliceNumber))[0], (getSlicePosition(sliceNumber))[1], (getSliceDimensions(sliceNumber))[0],  (getSliceDimensions(sliceNumber))[1]);
	return sliceMatrix;
}

int Image::getSliceSize(int sliceNumber){
	return _widthSlice[sliceNumber] * _heightSlice[sliceNumber] * 3;
}

int* Image::getSliceDimensions(int sliceNumber){
	int* size = new int[2];

	size[0] = _widthSlice[sliceNumber];
	size[1] = _heightSlice[sliceNumber];
	return size;
}

int* Image::getSlicePosition(int sliceNumber){
	int* position = new int[2];
	position[0] = 0;
	position[1] = 0;
	for(int i=0; i < sliceNumber;++i){
		position[0] += _widthSlice[i];
		//position[1] += _heightSlice[i]; //We divide in same height submatrixes
	}

	return position;
}
