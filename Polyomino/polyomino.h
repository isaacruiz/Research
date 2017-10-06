#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "admissible_factor.h"
//#include "boundary_words.h"
#include "../Suffix_Trie/node.h"
#include "../Suffix_Trie/suffixtrie.h"

using namespace std;

typedef vector<AdmissibleFactor>FactorVector;

class Polyomino
{
	public:
		
		Polyomino();
		Polyomino(string bw);
		~Polyomino();
		bool isBoundaryWord();
		bool tiles();  //cubic algorithm
		bool tiles2(); //linear algorithm
		void scale(int n);
		//void print();
		bool circularWord();
		bool clockwise();
		bool collision();
		int indexOfComplement(int i);
		void getFactors();
		void sortFactors();
		void sortFactorsByEnd(FactorVector &e, int* counter);
		void printFactors();
		void loadLookupVectors();
		void writeLongestFactorPair(ofstream& f);
		string boundString;
		SuffixTrie* st;
		FactorVector A;

		FactorVector* endIndexed;
		FactorVector* startIndexed;
		AdmissibleFactor* midIndexed;

		void printLookupVectors();
		//2 Arrays of vectors, index stores where the vector ends/starts
		//The vectors in the ending array sorts factors in order of longer to shorter
		//The vectors in the starting array sorts factors in order of shorter to longer
		//Another vector that holds factors by their midpoint

		int boundaryLength;

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
		int minX, maxX, minY, maxY;
};
#endif

