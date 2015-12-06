/*
 * Image.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "Image.h"
#include "Utils.h"
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

Image::Image(std::string filename) {
	// TODO Auto-generated constructor stub
	_filename = filename;

}

Image::~Image() {
	// TODO Auto-generated destructor stub
}


void Image::loadFromFile(){
	std::string line;
	std::ifstream infile(_filename);

	if (infile.is_open()){
		//Magic Number
		getline (infile,line);
		_magicNumber = line;
		getline (infile,line);

		//Width
		getline (infile,line);
		_width = std::stoi(line);
		getline (infile,line);

		//Height
		getline (infile,line);
		_height = std::stoi(line);
		getline (infile,line);

		//Max color value
		getline (infile,line);
		_maxColorValue = std::stoi(line);
		//int colorSize = ceil(log(_maxColorValue) / log(2));
		getline (infile,line);

		std::string tmpBinary;
		for(int y=0; y < _height; ++y){
			getline(infile, line);
			Pixel px = Pixel(0,0,0);

			std::vector<std::string> splittedLine = split(line, ' ');
			std::vector<Pixel> matrixLine;
			for(int x=0; x < _width; ++x){
				int rColor, gColor, bColor;

				tmpBinary = splittedLine[x*3];
				rColor = convertBinaryToDecimal(tmpBinary);

				tmpBinary = splittedLine[(x*3)+1];
				gColor = convertBinaryToDecimal(tmpBinary);

				tmpBinary = splittedLine[(x*3)+2];
				bColor = convertBinaryToDecimal(tmpBinary);

				px.setColor(rColor, gColor, bColor);
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

void Image::printMatrix(){
	for(int y=0; y < _height; ++y){
		for(int x=0; x < _width; ++x){
			std::cout << _matrix[y][x] << "\t\t\t";
		}
		std::cout << std::endl;
	}
}

Pixel Image::getPixel(int x, int y){
	if(x < 0)
		x = 0;
	if(x >= _width)
		x = _width-1;
	if(y < 0)
		y = 0;
	if(y >= _height)
		y = _height-1;

	return (_matrix.at(y)).at(x);
}

bool Image::isInMatrix(int x, int y){
	if ((0 <= x && x < _width) && (0 <= y && y < _height)){
		return true;
	}
	return false;
}

void Image::setMatrix(std::vector<std::vector<Pixel>>*& matrix){
	_matrix = *matrix;
}

std::vector<std::vector<Pixel>> Image::getMatrix(){
	return _matrix;
}

std::vector<Pixel> Image::getNeighboor(int x, int y){
	/*
	 * 			(0, -1)
	 * 	(-1,0)	(0,0)	(1, 0)
	 *			(0, 1)
	 */
	std::vector<Pixel> neighboor;
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
