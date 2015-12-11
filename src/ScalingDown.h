/*
 * ScalingDown.h
 *
 *  Created on: 6 déc. 2015
 *      Author: Maxime
 */

#ifndef SRC_SCALINGDOWN_H_
#define SRC_SCALINGDOWN_H_

#include "ScalingAlgorithm.h"

class ScalingDown: public ScalingAlgorithm  {
public:
	ScalingDown();
	ScalingDown(Image& image);
	ScalingDown(Image * const image);
	virtual ~ScalingDown();

	void chooseMethod(std::vector<std::vector<Pixel*>>*&  matrix, float factor, int x, int y);
	void divide(std::vector<std::vector<Pixel*>>*& matrix, float factor, int x, int y);
	void run(float factor) override;
};

#endif /* SRC_SCALINGDOWN_H_ */
