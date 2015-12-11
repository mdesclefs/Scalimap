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


void ScalingDown::chooseMethod(std::vector<std::vector<Pixel*>> *& matrix, float factor, int x, int y){
	if(factor != 0){
		factor = 1.0 / factor;
		this->divide(matrix, factor, x, y);
	}
}


/*
void ScalingDown::chooseMethod(float factor, int x, int y){
	if(factor != 0){
		this->divide(factor, x, y);
	}
}
*/

void ScalingDown::divide(std::vector<std::vector<Pixel*>> *& matrix, float factor, int x, int y){
	std::vector<Pixel*> rightClose;
	//rightClose.push_back(this->_image->getPixel(x, y));
	/*
	 * A B (0, 0) (1, 0)
	 * C D (0, 1) (1, 1)
	 * A B C (0, 0) (1, 0) (2, 0)
	 * D E F (0, 1) (1, 1) (2, 1)
	 * G H I (0, 2) (1, 2) (2, 2)
	 */
	for(int ny=0; ny<factor; ++ny){
		for(int nx=0; nx<factor; ++nx){
			if(this->_image->isInMatrix((factor*x)+nx, (factor*y)+ny)){
				rightClose.push_back(this->_image->getPixel((factor*x)+nx, (factor*y)+ny));
			}
		}
	}

	(*matrix)[y][x] = Utils::getAverage(rightClose);
}

/*
void ScalingDown::divide(float factor, int x, int y){
	std::vector<Pixel*> rightClose;
	//rightClose.push_back(this->_image->getPixel(x, y));
	/*
	 * A B (0, 0) (1, 0)
	 * C D (0, 1) (1, 1)
	 * A B C (0, 0) (1, 0) (2, 0)
	 * D E F (0, 1) (1, 1) (2, 1)
	 * G H I (0, 2) (1, 2) (2, 2)
	*\/

	factor = 1.0 / factor;

	std::cout << "factor : " << factor << std::endl;

	for(int ny=0; ny<factor; ++ny){
		for(int nx=0; nx<factor; ++nx){
			int newX, newY;
			newX = (factor*x) + nx;
			newY = (factor*y) + ny;
			if(this->_image->isInMatrix(nx, ny)){
				rightClose.push_back(this->_image->getPixel(nx, ny));
			}
		}
	}

	for(int ty=0; ty<factor; ++ty){
		int nx;
		if(ty == 0){
			//First line, we keep 0, 0;
			nx = x+1;
		}else{
			nx = x;
		}

		int line, begin, end;
		line = y+ty;
		begin = nx;
		end = x+(factor-1);

		std::cout << line << " at " << begin << ";" << end << std::endl;
		//(this->_image->getMatrix()[y+ty]).erase( (this->_image->getMatrix()[y+ty]).begin()+(nx), (this->_image->getMatrix()[y]).begin()+(x+factor));
	}

	this->_image->getMatrix()[y][x] = Utils::getAverage(rightClose);

	std::cout << "Après le average " << std::endl;
}
*/

void ScalingDown::run(float factor){
	factor = 1.0/(float) factor;
	ScalingAlgorithm::run(factor);
}
