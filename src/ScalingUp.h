/*
 * ScalingUp.h
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#ifndef SRC_SCALINGUP_H_
#define SRC_SCALINGUP_H_

#include "ScalingAlgorithm.h"

class ScalingUp: public ScalingAlgorithm {
public:
	ScalingUp();
	ScalingUp(Image& image);
	ScalingUp(Image * const image);
	virtual ~ScalingUp();

	void algorithm(float factor);
	void epx(std::vector<std::vector<Pixel>>* matrix, int x, int y);
	void advMAME3x(std::vector<std::vector<Pixel>>* matrix, int _x, int _y);

	bool threeOrMoreEqual(Pixel A, Pixel B, Pixel C, Pixel D);
};

#endif /* SRC_SCALINGUP_H_ */
