#include <iostream>

#include "polyomino.h"

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

int main()
{
	string boundaryWord;

	/*
	Boundary 1
	  ┌─┐
	  │ └───┐
	┌─┘     └─┐
	└─┐ ┌─┐ ┌─┘
	  └─┘ └─┘
	*/
	boundaryWord = "rdrrdrdldluldluluruu";  //Tiles by translation
	test(circularWord(boundaryWord));
	test(!collision(boundaryWord));
	test(clockwise(boundaryWord));

	boundaryWord = "ddldrdrurdrurulullul";
	test(!clockwise(boundaryWord));

	boundaryWord = "rdrrdrdldluldluluru"; //boundaryWord1, but missing last character to complete boundary
	test(!circularWord(boundaryWord));
	test(!collision(boundaryWord));
	test(clockwise(boundaryWord));

	/*
	Boundary 3
	┌─┐ ┌─┐
	│ └─┼─┘
	└───┘
	*/
	boundaryWord = "rdrrulddlluu";
	test(circularWord(boundaryWord));
	test(collision(boundaryWord));
	test(clockwise(boundaryWord));
	/*
	Boundary 4
	┌─┐ ┌─┐
	│ └─┘ │
	└─────┘
	*/

	boundaryWord = "rdrurddllluu"; //Does not tile by translation
	test(circularWord(boundaryWord));
	test(!collision(boundaryWord));
	test(clockwise(boundaryWord));
	/*
	Boundary 5
 	    ┌────┐
	    │    │ ┌─┐
    	└─┐  └─┘ │
	┌─────┘      └─┐
	└───┐    ┌─────┘ 
        │ ┌──┘
		└─┘
	*/
	boundaryWord = "rrddrurddrdllldldluullurrruluu"; //Has 2 zero length BN factorizations
	test(circularWord(boundaryWord));
	test(!collision(boundaryWord));
	//test(clockwise(boundaryWord)); Need to fix clockwise function

	cout << "Test complete" << endl;

	return 0;
}