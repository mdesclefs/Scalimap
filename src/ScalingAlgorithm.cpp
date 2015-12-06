/*
 * ScalingAlgorithm.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "ScalingAlgorithm.h"
#include <math.h>

ScalingAlgorithm::ScalingAlgorithm() : _image(NULL){
	// TODO Auto-generated constructor stub
}

ScalingAlgorithm::ScalingAlgorithm(Image& image) : _image(&image){
	// TODO Auto-generated constructor stub
}

ScalingAlgorithm::ScalingAlgorithm(Image * const image) : _image(image){
	// TODO Auto-generated constructor stub
}

ScalingAlgorithm::~ScalingAlgorithm() {
	// TODO Auto-generated destructor stub
}

void ScalingAlgorithm::algorithm(float factor){
	std::vector<std::vector<Pixel>> *newMatrix = new std::vector<std::vector<Pixel>>(this->_image->getHeight() * factor);

	for ( int i = 0 ; i < this->_image->getHeight() * factor ; i++ )
	   (*newMatrix)[i].resize(this->_image->getWidth() * factor);

	float translate = ceil(1 / factor);

	for(int y=0; y < this->_image->getHeight(); y+=translate){
		for(int x=0; x < this->_image->getWidth(); x+=translate){
			this->chooseMethod(newMatrix, factor, x, y);
		}
	}

	this->_image->factorSize(factor);
	this->_image->setMatrix(newMatrix);
}

void ScalingAlgorithm::run(float factor){
	this->algorithm(factor);
}
