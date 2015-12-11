/*
 * ScalingAlgorithm.h
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#ifndef SRC_SCALINGALGORITHM_H_
#define SRC_SCALINGALGORITHM_H_

#include "Image.h"

class ScalingAlgorithm {
protected:
	Image * const _image;
public:
	ScalingAlgorithm();
	ScalingAlgorithm(Image& image);
	ScalingAlgorithm(Image * const image);
	virtual ~ScalingAlgorithm();

	void algorithm(float factor);
	virtual void chooseMethod(std::vector<std::vector<Pixel*>>*& matrix, float factor, int x, int y) = 0;
	//virtual void chooseMethod(float factor, int x, int y) = 0;
	virtual void run(float factor);
};

#endif /* SRC_SCALINGALGORITHM_H_ */
