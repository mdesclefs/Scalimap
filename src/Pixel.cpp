/*
 * Pixel.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "Pixel.h"
#include "Utils.h"

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

void Pixel::toFile(std::string*& colorToString){
	return this->toFile(colorToString, 8);
}


void Pixel::toFile(std::string*& colorToString, int bitSize = 8){
	Utils::convertDecimalToBinary(colorToString, _color[0], bitSize);
	(*colorToString)+=" ";
	Utils::convertDecimalToBinary(colorToString, _color[1], bitSize);
	(*colorToString)+=" ";
	Utils::convertDecimalToBinary(colorToString, _color[2], bitSize);
	(*colorToString)+=" ";
}
