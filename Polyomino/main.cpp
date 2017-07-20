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
	//Boundary 1
	//┌─┐
	//└─┘
	//*/

	//Polyomino p1("rdlu");
	//test(p1.circularWord());
	//test(!p1.collision());
	//test(p1.clockwise());
	//test(p1.tiles());

	////Backtrack of Boundary 1
	//Polyomino p2("drul");
	//test(p2.circularWord());
	//test(!p2.collision());
	//test(!p2.clockwise());

	////Shift of Boundary 1
	//Polyomino p3("dlur");
	//test(p3.circularWord());
	//test(!p3.collision());
	//test(p3.clockwise());
	////test(tiles());

	////Backtrack of shift of Boundary 1
	//Polyomino p4("ruld");
	//test(p4.circularWord());
	//test(!p4.collision());
	//test(!p4.clockwise());


	/*
	Boundary 2
	  ┌─┐
	  │ └───┐
	┌─┘     └─┐
	└─┐ ┌─┐ ┌─┘
	  └─┘ └─┘
	*/
	Polyomino p5("rdrrdrdldluldluluruu");  //Tiles by translation
	test(p5.circularWord());
	test(!p5.collision());
	test(p5.clockwise());
	test(p5.tiles());

	Polyomino p6("rdrrdrdldluldluluruuu");  //Boundary 2 with extra character at end
	test(p6.collision());
	test(!p6.circularWord());
	test(!p6.tiles());

	Polyomino p7("ddldrdrurdrurulullul"); //Backtrack of Boundary 2
	test(!p7.clockwise());

	Polyomino p8("rdrrdrdldluldluluru");  //Boundary 2, but missing last character to complete boundary
	test(!p8.circularWord());
	test(!p8.collision());
	test(p8.clockwise());

	/*
	Boundary 3
	┌─┐ ┌─┐
	│ └─┼─┘
	└───┘
	*/
	Polyomino p9("rdrrulddlluu");
	test(p9.circularWord());
	test(p9.collision());
	//test(clockwise()); Clockwise method doesn't work for paths with loops
	
	/*
	Boundary 4
	┌─┐ ┌─┐
	│ └─┘ │
	└─────┘
	*/
	Polyomino p10("rdrurddllluu");//Does not tile by translation
	test(p10.circularWord());
	test(!p10.collision());
	test(p10.clockwise());
	test(!p10.tiles());
	
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
	Polyomino p11("rrddrurddrdllldldluullurrruluu");  //Has 2 zero length BN factorizations
	test(p11.circularWord());
	test(!p11.collision());
	test(p11.clockwise());
	test(p11.isBoundaryWord());
	test(p11.tiles());

	/*
	Boundary 6
      ┌─┐ ┌─┐
	┌─┘ └─┘ │   
	└─┐ ┌─┐ │
      └─┘ └─┘
	*/
	Polyomino p12("ururdrurdddluldlul");
	test(p12.circularWord());
	test(!p12.collision());
	test(p12.clockwise());
	test(p12.isBoundaryWord());
	test(p12.tiles());
	
	cout << "Tests completed" << endl;

	return 0;
}
