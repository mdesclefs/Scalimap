#include <iostream>
#include "Pixel.h"
#include "Image.h"
#include "ScalingUp.h"

int main(int argc, char **argv){

	//Pixel* px = new Pixel(125, 125, 125);

	Image* img = new Image("../images/test.ppm");
	img->loadFromFile();
	img->printMatrix();

	std::cout << "Scaling 2 : " << std::endl;
	ScalingUp* scaling = new ScalingUp(img);
	scaling->run(3);
	img->printMatrix();

	return(0);
}
