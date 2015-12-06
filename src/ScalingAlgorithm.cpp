/*
 * ScalingAlgorithm.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "ScalingAlgorithm.h"

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

void ScalingAlgorithm::run(float factor){
	this->algorithm(factor);
}
