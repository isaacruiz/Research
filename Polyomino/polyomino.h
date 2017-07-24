#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>

using namespace std;

class Polyomino
{
	public:
		
		Polyomino(string bw);
		~Polyomino();
		bool isBoundaryWord();
		bool tiles();

		//Helper functions
		bool circularWord();
		bool clockwise();
		bool collision();
	
	private:
		//returns the reverse complement
		string reverseComplement(string s);
		void sortCoordinates();
		struct coordinate
		{
			int x, y;
		};
		coordinate* coordinates;
		string boundaryWord;
		int minX, maxX, minY, maxY, wordLength;

};
#endif

