/*
 * Utils.h
 *
 *  Created on: 6 déc. 2015
 *      Author: Maxime
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>
#include <string>
#include "Pixel.h"

std::vector<std::string> split(const std::string& string, char delimiter);
int convertBinaryToDecimal(std::string tmpBinary);
Pixel* getAverage(std::vector<Pixel> &pixelList);

#endif /* SRC_UTILS_H_ */
