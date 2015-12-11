/*
 * Pixel.h
 *
 *  Created on: 5 déc. 2015
 *      Author: Maxime
 */
#ifndef SRC_PIXEL_H_
#define SRC_PIXEL_H_

#include <vector>
#include <iostream>

class Pixel {
private:
	std::vector<int> _color;
public:
	Pixel();
	Pixel(int rColor, int gColor, int bColor);
	virtual ~Pixel();

	std::vector<int> getColor() const;
	void setColor(int rColor, int gColor, int bColor);

	void toFile(std::string*& colorToString);
	void toFile(std::string*& colorToString, int bitSize);

	int& operator[] (int index){
		if(0 <= index && index < 3){
			return _color[index];
		}
		return _color[0];
	}

	int operator[] (int index) const{
		if(0 <= index && index < 3){
			return _color[index];
		}
		return _color[0];
	}

	friend bool operator==(const Pixel& lp, const Pixel& rp){
		std::vector<int> lColor, rColor;

		lColor = lp.getColor();
		rColor = rp.getColor();

		if(lColor[0] == rColor[0] && lColor[1] == rColor[1] && lColor[2] == rColor[2]){
			return true;
		}
		return false;
	}

	friend bool operator!=(const Pixel& lp, const Pixel& rp){return !(lp == rp);}

	friend std::ostream& operator<<(std::ostream& os, const Pixel& lp)
	{
	    os << "(" << lp.getColor()[0] << ',' << lp.getColor()[1] << ',' << lp.getColor()[2] << ")";
	    return os;
	}
};

#endif /* SRC_PIXEL_H_ */
