/*
 * Image.h
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */
#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#include <string>
#include <vector>
#include "Pixel.h"

class Image {
private:
	std::string _filename;
	std::vector<std::vector<Pixel>> _matrix;
	std::string _magicNumber;
	int _width = 0;
	int _height = 0;
	int _maxColorValue = 0;

public:
	Image(std::string filename);
	virtual ~Image();

	void loadFromFile();
	void printMatrix();

	Pixel getPixel(int x, int y);
	bool isInMatrix(int x, int y);

	void setMatrix(std::vector<std::vector<Pixel>>*& matrix);
	std::vector<std::vector<Pixel>> getMatrix();
	std::vector<Pixel> getNeighboor(int x, int y);

	void factorSize(float size){
		_width*=size;
		_height*=size;
	}

	int getWidth(){
		return _width;
	}

	int getHeight(){
		return _height;
	}

	friend std::ostream& operator<<(std::ostream& os, const Image& image)
	{
		for(int y=0; y < image._height; ++y){
			for(int x=0; x < image._width; ++x){
				os << "(" << x << "," << y << ")\n";
				os << image._matrix[y][x] << "\t\t\t";
			}
			os << "\n";
		}
		return os;
	}
};

#endif /* SRC_IMAGE_H_ */
