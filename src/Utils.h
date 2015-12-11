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
#include "ScalingAlgorithm.h"

class Utils{
public:
	static std::vector<std::string> split(const std::string& string, char delimiter);
	static int convertBinaryToDecimal(std::string& tmpBinary);
	static void convertDecimalToBinary(std::string*& colorToString, int tmpDecimal);
	static void convertDecimalToBinary(std::string*& colorToString, int tmpDecimal, int bitSize);
	static Pixel* getAverage(std::vector<Pixel*> &pixelList);
	static int** initMatrixToSend(int width, int height);
	static ScalingAlgorithm* chooseAlgorithm(std::string method, Image*& subImage);
	static float getFactor(std::string method, int factor);
	static bool isInteger(float value);
	static int* decomposeFactor(float factor);
};

#endif /* SRC_UTILS_H_ */
