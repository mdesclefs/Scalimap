/*
 * Pixel.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "Pixel.h"

Pixel::Pixel() {}

Pixel::Pixel(int rColor, int gColor, int bColor) {
	// TODO Auto-generated constructor stub
	_color.push_back(rColor);
	_color.push_back(gColor);
	_color.push_back(bColor);
}

Pixel::~Pixel() {
	// TODO Auto-generated destructor stub
}

std::vector<int> Pixel::getColor() const{
	return _color;
}

void Pixel::setColor(int rColor, int gColor, int bColor){
	_color[0] = rColor;
	_color[1] = gColor;
	_color[2] = bColor;
}
