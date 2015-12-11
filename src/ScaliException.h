/*
 * Exceptions.h
 *
 *  Created on: 7 déc. 2015
 *      Author: Maxime
 */

#ifndef SRC_SCALIEXCEPTION_H_
#define SRC_SCALIEXCEPTION_H_

#include <exception>
#include <iostream>

class ScaliException : public std::exception{

public:
	static ScaliException* Exception;
	static const char* exceptionMessage;
	ScaliException();
	virtual ~ScaliException() throw();

	static ScaliException*& ArgumentFailure(){
		exceptionMessage = "Launching command has to be like this : ./Scalimap <image_filename> <option> <factor>";
		return Exception;
	}

	static ScaliException*& NullProcessorNumber(){
		exceptionMessage = "U Should at least use one processor.";
		return Exception;
	}

	static ScaliException*& NullFactor(){
		exceptionMessage = "The factor must be over 1.";
		return Exception;
	}

	static ScaliException*& MethodArgument(){
		exceptionMessage = "Option must be : U(p), u(p), D(own), d(own).";
		return Exception;
	}

	static ScaliException*& SubimageEmpty(){
		exceptionMessage = "The Subimage you are trying to load is empty.";
		return Exception;
	}

	static ScaliException*& MultipleTwoThree(){
		exceptionMessage = "The factor must be a multiple of two and/or three.";
		return Exception;
	}


	virtual const char* what() const throw(){
		return exceptionMessage;
	}

};

#endif /* SRC_SCALIEXCEPTION_H_ */
