#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "admissible_factor.h"
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
		bool circularWord();
		bool clockwise();
		bool collision();
		bool tiles();  //cubic algorithm
		bool tiles2(); //linear algorithm
		
		int indexOfComplement(int i);
		void getFactors();
		void sortFactors();
		void sortFactorsByEnd(FactorVector &e, int* counter);
		void loadLookupVectors();
		
		//Debugging methods
		void printFactors();
		void printCoordinates();
		void printLookupVectors();
		void writeLongestFactorPair(ofstream& f);
		void scale(int n);
		//void print();
		

	private:
		//returns the reverse complement
		string reverseComplement(string s);
		void sortCoordinates();
		void getCoordinates();
		struct coordinate
		{
			int x, y;
		};
		
		string boundString; //concatenation of the boundaryWord twice and its reverse complement
		string boundaryWord;
		SuffixTrie* st;
		FactorVector A; //Vector of all the unsorted admissible factors
		FactorVector* endIndexed;
		FactorVector* startIndexed;
		AdmissibleFactor* midIndexed;
		int boundaryLength;

		coordinate* coordinates;
		
		int minX, maxX, minY, maxY;
};
#endif

