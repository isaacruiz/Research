#include <iostream>
#include <stdlib.h>
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
	string bw;
	
	/*
	Boundary 1
	┌─┐
	└─┘
	*/
	bw = "rdlu";
	test(circularWord(bw));
	test(!collision(bw));
	test(clockwise(bw));

	//Backtrack of Boundary 1
	bw = "drul"; 
	test(circularWord(bw));
	test(!collision(bw));
	test(!clockwise(bw));

	//Shift of Boundary 1
	bw = "dlur";
	test(circularWord(bw));
	test(!collision(bw));
	test(clockwise(bw));

	//Backtrack of shift of Boundary 1
	bw = "ruld";
	test(circularWord(bw));
	test(!collision(bw));
	test(!clockwise(bw));


	/*
	Boundary 2
	  ┌─┐
	  │ └───┐
	┌─┘     └─┐
	└─┐ ┌─┐ ┌─┘
	  └─┘ └─┘
	*/
	bw = "rdrrdrdldluldluluruu";  //Tiles by translation
	test(circularWord(bw));
	test(!collision(bw));
	test(clockwise(bw));

	bw = "rdrrdrdldluldluluruuu";  //Boundary 2 with extra character at end
	test(collision(bw));
	test(!circularWord(bw));

	bw = "ddldrdrurdrurulullul"; //Backtrack of Boundary 2
	test(!clockwise(bw));

	bw = "rdrrdrdldluldluluru"; //Boundary 2, but missing last character to complete boundary
	test(!circularWord(bw));
	test(!collision(bw));
	test(clockwise(bw));

	/*
	Boundary 3
	┌─┐ ┌─┐
	│ └─┼─┘
	└───┘
	*/
	bw = "rdrrulddlluu";
	test(circularWord(bw));
	test(collision(bw));
	//test(clockwise(bw)); Clockwise method doesn't work for paths with loops
	
	/*
	Boundary 4
	┌─┐ ┌─┐
	│ └─┘ │
	└─────┘
	*/
	bw = "rdrurddllluu"; //Does not tile by translation
	test(circularWord(bw));
	test(!collision(bw));
	test(clockwise(bw));
	
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

	bw = "rrddrurddrdllldldluullurrruluu"; //Has 2 zero length BN factorizations
	test(circularWord(bw));
	test(!collision(bw));
	test(clockwise(bw));
	test(isBoundaryWord(bw));

	cout << "Tests completed" << endl;

	return 0;
}
