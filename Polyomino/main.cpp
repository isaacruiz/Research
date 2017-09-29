#include "polyomino.h"

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file << ", line " << line << "." << endl;
	abort();
}
#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

int main()
{
	//Boundary 1
	//┌─┐
	//└─┘
	//*/
	Polyomino b1("nesw");
	test(b1.circularWord());
	test(!b1.collision());
	test(b1.clockwise());
	test(b1.tiles());
	test(b1.tiles2());

	//Backtrack of Boundary 1
	Polyomino p2("senw");
	test(p2.circularWord());
	test(!p2.collision());
	test(!p2.clockwise());
	//test(!p2.tiles());
	//test(!p2.tiles2());

	////Shift of Boundary 1
	Polyomino p3("swne");
	test(p3.circularWord());
	//test(!p3.collision());
	test(p3.clockwise());
	test(p3.tiles());

	//Backtrack of shift of Boundary 1
	Polyomino p4("enws");
	test(p4.circularWord());
	test(!p4.collision());
	test(!p4.clockwise());

	////Boundary 2
	////  ┌─┐
	////  │ └───┐
	////┌─┘     └─┐
	////└─┐ ┌─┐ ┌─┘
	////  └─┘ └─┘
	////*/
	Polyomino b2("neseeseswswnwswnwnen");
	test(b2.circularWord());
	test(!b2.collision());
	test(b2.clockwise());
	test(b2.tiles());
	test(b2.tiles2());
	
	Polyomino b2_2("eseeseswswnwswnwnennn");  //Boundary 2 with extra character at end
	//test(b2_2.collision());  //Does not test true with sorted coordinate algorithm
	test(!b2_2.circularWord());
	test(!b2_2.tiles());
	test(!b2_2.tiles2());

	Polyomino b2_3("sswsesenesenenwnwwnw"); //Backtrack of Boundary 2
	test(!b2_3.clockwise());
	//test(!b2_3.tiles());
	//test(!b2_3.tiles2());
	
	Polyomino b2_4("eseeseswswnwswnwnen");  //Boundary 2, but missing last character to complete boundary
	test(!b2_4.circularWord());
	test(!b2_4.collision());
	test(b2_4.clockwise());
	///*
	//Boundary 3
	//         ┌─┐ ┌─┐
	//       ┌─┘ └─┘ │   
	//       └─┐ ┌─┐ │
	//         └─┘ └─┘
	//*/
	
	Polyomino b3("nenesenessswnwswnw");
	test(b3.circularWord());
	test(!b3.collision());
	test(b3.clockwise());
	test(b3.isBoundaryWord());
	test(b3.tiles());
	test(b3.tiles2());
	
	///*
	//Boundary 4
	//       ┌────┐
	//       │    │ ┌─┐
	//       └─┐  └─┘ │
	//   ┌─────┘      └─┐
	//   └───┐    ┌─────┘ 
	//       │ ┌──┘
	//       └─┘
	//*/
	Polyomino b4("eessenesseswwwswswnnwwneeenwnn");
	test(b4.circularWord());
	test(!b4.collision());
	test(b4.clockwise());
	test(b4.isBoundaryWord());
	test(b4.tiles());
	test(b4.tiles2());
	
	Polyomino b4_2("sseswwwswswnnwwneeenwnneessene");
	test(b4_2.circularWord());
	test(!b4_2.collision());
	test(b4_2.clockwise());
	test(b4_2.isBoundaryWord());
	test(b4_2.tiles());
	test(b4_2.tiles2());

	//Boundary 5
	//┌──────┐
	//│      │
	//│      │
	//└──────┘

	Polyomino b5("nnnneeeesssswwww");
	test(b5.tiles());
	test(b5.tiles2());



	//Boundary 6
	//┌─┐ ┌─┐
	//│ └─┘ │
	//└─────┘
	//*/
	
	Polyomino b6("esenesswwwnn");//Does not tile by translation
	test(b6.circularWord());
	test(!b6.collision());
	test(b6.clockwise());
	test(!b6.tiles());
	test(!b6.tiles2());

	Polyomino b7("nnesenenessswwww");
	test(!b7.tiles());
	test(!b7.tiles2());

	///*
	//Boundary 8
	//┌─┐ ┌─┐
	//│ └─┼─┘
	//└───┘
	//*/

	Polyomino b8("eseenwsswwnn");
	test(b8.circularWord());
	test(b8.collision());
	//test(b8.clockwise()); //Clockwise method doesn't work for paths with loops
	//test(!b8.tiles());
	//test(!b8.tiles2());


	//Timing tests-------------------------------------------------------------------------------------------------------------------------------!
	//clock_t start;
	//clock_t end;
	//double duration;
	//const int COUNT = 5;
	//int factor = 128;
	//Polyomino* p[COUNT];
	//double totalTime = 0;
	//for (int i = 0; i < COUNT; i++)
	//{//eseeseswswnwswnwnenn tiles
	//	//neneneeseesswswwnwww does not tile
	//	p[i] = new Polyomino("eseeseswswnwswnwnenn");

	//	p[i]->scale(factor); //Scales boundary word by argument and randomizes the start point
	//}
	//
	//for (int i = 0; i < COUNT; i++)
	//{
	//	start = clock();
	//	test(p[i]->tiles());
	//	end = clock();
	//	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	//	totalTime += duration;
	//	cout << duration << endl;
	//}
	//
	//

	//cout << "Tests took a total of " << totalTime << "\tseconds\n";
	//cout << "Tests completed" << endl;

	//for (int i = 0; i < COUNT; i++)
	//	delete p[i];
	//-------------------------------------------------------------------------------------------------------------------------------------------!

	cout << "Test completed" << endl;
	return 0;
}

