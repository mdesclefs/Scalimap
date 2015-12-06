/*
 * Utils.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */

#include <sstream>
#include <vector>
#include <string>
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
