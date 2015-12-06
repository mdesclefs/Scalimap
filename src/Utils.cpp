/*
 * Utils.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include "Utils.h"
#include <sstream>
#include <math.h>

std::vector<std::string> split(const std::string& string, char delimiter)
{
    std::istringstream split(string);
    std::vector<std::string> items;
    for (std::string tmp; std::getline(split, tmp, ' '); items.push_back(tmp));
    return items;
}

int convertBinaryToDecimal(std::string tmpBinary){
	int dec = 0;
	reverse(tmpBinary.begin(), tmpBinary.end());
	for (int i = 0; i < tmpBinary.size(); ++i) {
		dec += (int(tmpBinary[i]) - 48)*pow(2, i);
	}

	return dec;
}

Pixel* getAverage(std::vector<Pixel> &pixelList){
	int listSize = pixelList.size();
	if(listSize > 0){
		int rColor = 0;
		int gColor = 0;
		int bColor = 0;

		for(std::vector<Pixel>::iterator it=pixelList.begin() ; it < pixelList.end(); ++it ) {
			rColor+= ((Pixel)(*it)).getColor()[0];
			gColor+= ((Pixel)(*it)).getColor()[1];
			bColor+= ((Pixel)(*it)).getColor()[2];
		}

		rColor/=listSize;
		gColor/=listSize;
		bColor/=listSize;

		pixelList[0].setColor(rColor, gColor, bColor);

		return &pixelList[0];
	}
	return nullptr;
}
