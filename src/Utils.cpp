/*
 * Utils.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "Utils.h"
#include "ScalingUp.h"
#include "ScalingDown.h"
#include <sstream>
#include <math.h>

std::vector<std::string> Utils::split(const std::string& string, char delimiter)
{
    std::istringstream split(string);
    std::vector<std::string> items;
    for (std::string tmp; std::getline(split, tmp, ' '); items.push_back(tmp));
    return items;
}

int Utils::convertBinaryToDecimal(std::string& tmpBinary){
	int dec = 0;
	reverse(tmpBinary.begin(), tmpBinary.end());
	for (int i = 0; i < tmpBinary.size(); ++i) {
		dec += (int(tmpBinary[i]) - 48)*pow(2, i);
	}

	return dec;
}

void Utils::convertDecimalToBinary(std::string*& colorToString, int tmpDecimal){
	return Utils::convertDecimalToBinary(colorToString, tmpDecimal, 8);
}

void Utils::convertDecimalToBinary(std::string*& colorToString, int tmpDecimal, int bitSize){
	std::string binary = "";
	int dec = 2;
	while(dec < tmpDecimal){
		dec*=2;
		binary+="1";
	}

	if((dec-1) != tmpDecimal){
		int size = binary.size();
		binary = "";

		for(int i=0; i < size; ++i){
			binary+="0";
		}

		binary="1" + binary;
	}

	while(binary.size() < bitSize){
		binary="0"+binary;
	}

	(*colorToString) += binary;
}

Pixel* Utils::getAverage(std::vector<Pixel*> &pixelList){
	int listSize = pixelList.size();
	if(listSize > 0){
		int rColor = 0;
		int gColor = 0;
		int bColor = 0;

		for(std::vector<Pixel*>::iterator it=pixelList.begin() ; it < pixelList.end(); ++it ) {
			rColor+= ((Pixel*)(*it))->getColor()[0];
			gColor+= ((Pixel*)(*it))->getColor()[1];
			bColor+= ((Pixel*)(*it))->getColor()[2];
		}

		rColor/=listSize;
		gColor/=listSize;
		bColor/=listSize;

		pixelList[0]->setColor(rColor, gColor, bColor);

		return pixelList[0];
	}
	return nullptr;
}

int** Utils::initMatrixToSend(int width, int height){
	int *row = (int *) malloc(3*width*height*sizeof(int));
	int **slicedMatrix = (int **) malloc(height*sizeof(int*));
	for (int y=0; y<height; ++y){
		slicedMatrix[y] = &(row[y*width*3]);
	}

	return slicedMatrix;
}

ScalingAlgorithm* Utils::chooseAlgorithm(std::string method, Image*& subImage){
	ScalingAlgorithm* scaling;
	if(method == "U" || method == "u"){
		scaling = new ScalingUp(subImage);
	}else{
		scaling = new ScalingDown(subImage);
	}
	return scaling;
}

float Utils::getFactor(std::string method, int factor){
	float newFactor = factor;
	if(method == "D" || method == "d")
		newFactor = 1.0/ newFactor;

	return newFactor;
}
