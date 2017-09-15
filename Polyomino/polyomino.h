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
#include <iomanip>

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
		bool circularWord();
		bool clockwise();
		bool collision();
		int indexOfComplement(int i);
		void getFactors();
		void sortFactors();
		void printFactors();
		void printFactorArray();
		string boundString;
		SuffixTrie* st;
		vector <AdmissibleFactor> A;
		vector <vector <AdmissibleFactor>> factorArray;

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

