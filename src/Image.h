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
#include <math.h>
#include "Pixel.h"


class Image {
private:
	std::string _filename;
	std::vector<std::vector<Pixel*>> _matrix;
	std::string _magicNumber;

	int _width;
	int _height;
	std::vector<int> _widthSlice;
	std::vector<int> _heightSlice;

	int _maxColorValue;

    //std::vector<std::vector<int, int>> _slices;

public:
	Image(std::string filename);
	Image(int* sliceSize, int** intMatrix);
	virtual ~Image();

	void loadFromFile();
	void saveInFile(std::string& method, int factor);
	void printMatrix();

	//Pixel getPixel(int x, int y);
	Pixel*& getPixel(int x, int y);
	bool isInMatrix(int x, int y);

	void resetMatrix();
	void setMatrix(std::vector<std::vector<Pixel*>>*& matrix);
	std::vector<std::vector<Pixel*>> getMatrix();
	int** getMatrixToSend();
	int** initMatrixInRange(int xStart, int yStart, int xOffset, int yOffset);
	std::vector<Pixel*> getNeighboor(int x, int y);

	void updateSlice(int sliceNumber, int** slice);
	void setSlice(int procNbr);
	int** getSlice(int sliceNumber);
	int getSliceSize(int sliceNumber);
	int* getSliceDimensions(int sliceNumber);
	int* getSlicePosition(int sliceNumber);

	void factorSize(float size){
		if(_widthSlice.size() == 0){
			_width= floor(_width * size);
			_height= floor(_height * size);
		}else{
			_width= 0;
			_height= 0;
			for(int i=0; i < (int) _widthSlice.size(); ++i){
				_widthSlice[i] = floor(_widthSlice[i]*size);
				_heightSlice[i] = floor(_heightSlice[i]*size);

				_width += _widthSlice[i];
				_height = _heightSlice[i];
			}
		}
	}


	int getWidth(){
		return _width;
	}

	int getHeight(){
		return _height;
	}

	int getMaxBitsColor(){
		//return (log(_maxColorValue)/log(2.0));
		return (ceil(log(_maxColorValue) / log(2)) / 8);
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
