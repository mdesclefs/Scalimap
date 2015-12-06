/*
 * ScalingDown.cpp
 *
 *  Created on: 6 déc. 2015
 *      Author: Maxime
 */

#include "ScalingDown.h"
#include "Utils.h"
#include <math.h>

ScalingDown::ScalingDown() : ScalingAlgorithm() {
	// TODO Auto-generated constructor stub

}

ScalingDown::ScalingDown(Image& image) : ScalingAlgorithm(&image) {
	// TODO Auto-generated constructor stub

}

ScalingDown::ScalingDown(Image * const image) : ScalingAlgorithm(image) {
	// TODO Auto-generated constructor stub

}

ScalingDown::~ScalingDown() {
	// TODO Auto-generated destructor stub
}

void ScalingDown::chooseMethod(std::vector<std::vector<Pixel>> *& matrix, float factor, int x, int y){
	if(factor != 0)
		this->divide(matrix, (1*factor), x, y);
}

void ScalingDown::divide(std::vector<std::vector<Pixel>> *& matrix, float factor, int x, int y){
	std::vector<Pixel> rightClose;
	rightClose.push_back(this->_image->getPixel(x, y));
	/*
	 * A B (0, 0) (1, 0)
	 * C D (0, 1) (1, 1)
	 * A B C (0, 0) (1, 0) (2, 0)
	 * D E F (0, 1) (1, 1) (2, 1)
	 * G H I (0, 2) (1, 2) (2, 2)
	 */
	factor = ceil(1 / factor);
	for(int ny=0; ny<factor; ++ny){
		for(int nx=0; nx<factor; ++nx){
			if(this->_image->isInMatrix(nx, ny))
				rightClose.push_back(this->_image->getPixel(nx, ny));
		}
	}

	(*matrix)[x][y] = (*getAverage(rightClose));
}
