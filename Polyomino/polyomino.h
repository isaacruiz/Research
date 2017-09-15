#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include "admissible_factor.h"
#include "../Suffix_Trie/node.h"
#include "../Suffix_Trie/suffixtrie.h"

using namespace std;

class Polyomino
{
	public:
		
		Polyomino(string bw);
		~Polyomino();
		bool isBoundaryWord();
		bool tiles();
		void scale(int n);
		//void print();
		//Helper functions
		bool circularWord();
		bool clockwise();
		bool collision();
		SuffixTrie* st;
		vector <AdmissibleFactor> A;
		int indexOfComplement(int i);
		string boundString;

		void getFactors();
		void sortFactors();
		void printFactors();
	private:
		//returns the reverse complement
		string reverseComplement(string s);
		void sortCoordinates();
	
		void setCoordinates();
		struct coordinate
		{
			int x, y;
		};
		coordinate* coordinates;
		string boundaryWord;
		int minX, maxX, minY, maxY, boundaryLength;

};
#endif

