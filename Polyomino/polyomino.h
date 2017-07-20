#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>

using namespace std;

class Polyomino
{
	public:
		
		Polyomino(string bw);
		bool isBoundaryWord();
		bool tiles();

		//Helper functions
		bool circularWord();
		bool clockwise();
		bool collision();
	
	private:
		//returns the reverse complement
		string reverseComplement(string s);
		void radixSort(int **arr);
		
		struct coordinate
		{
			int x, y;
		};

		string boundaryWord;
		int maxX, maxY, wordLength;

};
#endif

