#include "polyomino.h"

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file << ", line " << line << "." << endl;
	abort();
}
#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

int main()
{
	///*
	//Boundary 1
	//┌─┐
	//└─┘
	//*/
	////Add tests for long words
	//Polyomino p1("eswn");
	//test(p1.circularWord());
	//test(!p1.collision());
	//test(p1.clockwise());
	//test(p1.tiles());
	//p1.print();
	////Backtrack of Boundary 1
	//Polyomino p2("senw");
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

	///*
	////Boundary 2
	////  ┌─┐
	////  │ └───┐
	////┌─┘     └─┐
	////└─┐ ┌─┐ ┌─┘
	////  └─┘ └─┘
	////*/
	//Polyomino p5("rdrrdrdldluldluluruu");  //Tiles by translation
	//test(p5.circularWord());
	//test(!p5.collision());
	//test(p5.clockwise());
	//test(p5.tiles());
	//p5.print();
	//Polyomino p6("rdrrdrdldluldluluruuu");  //Boundary 2 with extra character at end
	////test(p6.collision());  //Does not test true with sorted coordinate algorithm
	//test(!p6.circularWord());
	//test(!p6.tiles());

	//Polyomino p7("ddldrdrurdrurulullul"); //Backtrack of Boundary 2
	//test(!p7.clockwise());

	//Polyomino p8("rdrrdrdldluldluluru");  //Boundary 2, but missing last character to complete boundary
	//test(!p8.circularWord());
	//test(!p8.collision());
	//test(p8.clockwise());

	///*
	//Boundary 3
	//┌─┐ ┌─┐
	//│ └─┼─┘
	//└───┘
	//*/

	//Polyomino p9("rdrrulddlluu");
	//test(p9.circularWord());
	//test(p9.collision());
	////test(clockwise()); Clockwise method doesn't work for paths with loops
	//
	///*
	//Boundary 4
	//┌─┐ ┌─┐
	//│ └─┘ │
	//└─────┘
	//*/
	//Polyomino p10("rdrurddllluu");//Does not tile by translation
	//test(p10.circularWord());
	//test(!p10.collision());
	//test(p10.clockwise());
	//test(!p10.tiles());

	///*
	//Boundary 5
 //       ┌────┐
 //       │    │ ┌─┐
 //       └─┐  └─┘ │
 //   ┌─────┘      └─┐
 //   └───┐    ┌─────┘ 
 //       │ ┌──┘
 //       └─┘
	//*/
	//Polyomino p11("eessenesseswwwswswnnwwneeenwnn");  //Has 2 zero length BN factorizations
	//test(p11.circularWord());
	//test(!p11.collision());
	//test(p11.clockwise());
	//test(p11.isBoundaryWord());
	//test(p11.tiles());

	///*
	//Boundary 6
 //         ┌─┐ ┌─┐
 //       ┌─┘ └─┘ │   
 //       └─┐ ┌─┐ │
 //         └─┘ └─┘
	//*/
	//Polyomino p12("ururdrurdddluldlul");
	//test(p12.circularWord());
	//test(!p12.collision());
	//test(p12.clockwise());
	//test(p12.isBoundaryWord());
	//test(p12.tiles());
	

	//Timing tests
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
	

	//cout << "Factors for boundary word nesw:\n";
	//Polyomino b1("nesw");
	//cout << "Boundary word length: " << b1.boundaryLength << endl;
	//b1.printFactors();
	//b1.printLookupVectors();
	//test(b1.tiles());

	cout << "\nFactors for boundary word neseeseswswnwswnwnen:\n";
	Polyomino b2("neseeseswswnwswnwnen");
	cout << "Boundary word length: " << b2.boundaryLength << endl;
	b2.printFactors();
	b2.printLookupVectors();
	test(b2.tiles());
	

	/*Polyomino b3("nenesenessswnwswnw");
	cout << "\nFactors for boundary word nenesenessswnwswnw:\n";
	cout << "Boundary word length: " << b3.boundaryLength << endl;
	b3.printFactors();
	b3.printLookupVectors();
	test(b3.tiles());
	
	
	Polyomino b4("eessenesseswwwswswnnwwneeenwnn");
	cout << "\nFactors for boundary word eessenesseswwwswswnnwwneeenwnn:\n";
	cout << "Boundary word length: " << b4.boundaryLength << endl;
	b4.printFactors();
	b4.printLookupVectors();
	test(b4.tiles());
	
	cout << "\nFactors for boundary word nnnneeeesssswwww:\n";
	Polyomino b5("nnnneeeesssswwww");
	cout << "Boundary word length: " << b5.boundaryLength << endl;
	b5.printFactors();
	b5.printLookupVectors();
	test(b5.tiles());*/

	cout << "\nTest completed" << endl;
	return 0;
}

/*
a + b <= n/2
int bi = 0;

for (each A that ends at W[i]
	while (B[bi[.length + A.length <=2)
		==Bi;
	--bi;
	int c.start = B.[Bi].end]+1
	int cend = (A.begin + n/2 + n) % n
//make containers for each start and end point at each position for all admissible factors
*/