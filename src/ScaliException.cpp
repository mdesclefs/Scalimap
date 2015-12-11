/*
 * Exceptions.cpp
 *
 *  Created on: 7 déc. 2015
 *      Author: Maxime
 */

#include "ScaliException.h"

const char* ScaliException::exceptionMessage = "";
ScaliException* ScaliException::Exception = new ScaliException();

ScaliException::ScaliException() {
	// TODO Auto-generated constructor stub

}

ScaliException::~ScaliException() {
	// TODO Auto-generated destructor stub
}

