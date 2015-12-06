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

	virtual void algorithm(float factor) = 0;
	void run(float factor);
};

#endif /* SRC_SCALINGALGORITHM_H_ */
