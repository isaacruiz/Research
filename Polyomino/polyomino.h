#ifndef POLYOMINO_H
#define POLYOMINO_H

#include <string>
using namespace std;

bool isBoundaryWord(string s);
bool tiles(string s);

//Helper functions
bool enclosed(string s);
bool clockwise(string s);
bool collision(string s);

#endif

