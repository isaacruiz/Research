#include "polyomino.h"
#include <fstream>
//#include "boundary_words.h"

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

	//cout << blah[1];
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
	test(!p2.tiles());
	test(!p2.tiles2());

	////Shift of Boundary 1
	Polyomino p3("swne");
	test(p3.circularWord());
	test(!p3.collision());
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
	
	Polyomino b2_2("neseeseswswnwswnwnenn");  //Boundary 2 with extra character at end
	
	
	test(b2_2.collision());  //Does not test true with sorted coordinate algorithm
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
	test(!b8.clockwise());
	test(!b8.tiles());
	test(!b8.tiles2());


	ifstream in;
	in.open("boundary_words.txt");
	
	ofstream out;
	out.open("output2.txt");

	if (!out || !in)
	{
		cerr << "Unable to open files\n";
		exit(1);
	}

	const int SIZE = 15000;
	string words[SIZE];
	Polyomino* p[SIZE];
	int i = 0;
	while (!in.eof() && i < SIZE)
	{
		in >> words[i];
		p[i] = new Polyomino(words[i]);
		++i;
	}

	for (i = 0; i < SIZE; ++i)
	{
		test(p[i]->tiles() == p[i]->tiles2());
	}

	////Print out tiling data
	//out << "                 Boundary Word    |W|   Max |A|+|B|         FactorA         FactorB  Tiles(Alg1)  Tiles(Alg2)  Tiling Disagreement |A|+|B| > |W|/2" << endl;
	//b1.writeLongestFactorPair(out);
	//b2.writeLongestFactorPair(out);
	//b3.writeLongestFactorPair(out);
	//b4.writeLongestFactorPair(out);
	//b5.writeLongestFactorPair(out);
	//b6.writeLongestFactorPair(out);
	//b7.writeLongestFactorPair(out);
	//b8.writeLongestFactorPair(out);
	//for (i = 0; i < SIZE; ++i)
	//{
	//	p[i]->writeLongestFactorPair(out);
	//}

	in.close();
	//out.close();

	

	////Test boundary word for all possible starting positions
	//Polyomino* poly[20];
	//string bw = "neeseeswwwnw";
	//ofstream start;
	//start.open("start.txt");

	//for (int i = 0; i < bw.length(); i++) {
	//	
	//	string modBW = bw.substr(i, bw.length() - i) + bw.substr(0, i);
	//	poly[i] = new Polyomino(modBW);
	//	poly[i]->writeLongestFactorPair(start);
	//}


	//poly[0]->printLookupVectors();
	//poly[0]->printFactors();



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

