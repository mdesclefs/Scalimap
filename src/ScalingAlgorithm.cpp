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
	int newHeight = floor((this->_image->getHeight() * factor));
	int newWidth = floor((this->_image->getWidth() * factor));

	std::vector<std::vector<Pixel*>> *newMatrix = new std::vector<std::vector<Pixel*>>(newHeight);
	for ( int i = 0 ; i < newHeight ; i++ )
	   (*newMatrix)[i].resize(newWidth);

	float trans = 1;
	if(factor < 1){
		trans = factor;
	}

	for(int y=0; y < floor((this->_image->getHeight() * trans)); ++y){
		for(int x=0; x < floor((this->_image->getWidth() * trans)); ++x){
 			this->chooseMethod(newMatrix, factor, x, y);
		}
	}

	this->_image->factorSize(factor);
	this->_image->setMatrix(newMatrix);
}

void ScalingAlgorithm::run(float factor){
	this->algorithm(factor);
}
