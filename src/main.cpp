#include <iostream>

#include "Utils.h"
#include "Pixel.h"
#include "Image.h"
#include "ScalingUp.h"
#include "ScalingDown.h"

int main(int argc, char **argv){

	//Pixel* px = new Pixel(125, 125, 125);

	Image* img = new Image("../images/test3x3.ppm");
	img->loadFromFile();
	img->printMatrix();

	//std::cout << "Scaling 2 : " << std::endl;
	//ScalingUp* scaling = new ScalingUp(img);
	std::cout << "Scaling 1/2 : " << std::endl;
	ScalingDown* scaling = new ScalingDown(img);
	scaling->run(1.0/3.0);

	img->printMatrix();

	return(0);
}
