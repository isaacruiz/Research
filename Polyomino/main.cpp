#include <iostream>
#include <unordered_set>

#include "polyomino.h"


int main()
{
	unordered_set<string> test = { "this", "is", "a", "test" };

	unordered_set<string>::const_iterator g = test.end();
	for (g = test.begin(); g != test.end(); g++)
	{
		cout << *g << endl;
	}

	return 0;
}