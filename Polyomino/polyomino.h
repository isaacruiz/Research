#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>
using namespace std;

bool isBoundaryWord(string s);
bool tiles(string s);

//Helper functions
bool circularWord(string s);
bool clockwise(string s);
bool collision(string s);
//returns the reverse complement
string reverseComplement(string s);
void printPolyomino(string s);

#endif

