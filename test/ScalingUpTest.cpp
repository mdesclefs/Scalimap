#include <cppunit/TestCase.h>

#include "../src/ScalingUp.h"

class ScalingUpTest : public CppUnit::TestCase {
public:
	ScalingUpTest(std::string name) : CppUnit::TestCase(name){
		Image* img = new Image("../images/test.ppm");
		ScalingUp algo = ScalingUp(img);
	}

	void runTest() {
		/*CPPUNIT_ASSERT( Complex (10, 1) == Complex (10, 1) );*/
	}
};
