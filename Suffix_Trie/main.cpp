#include <iostream>
#include "suffixtrie.h"

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
        abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

using namespace std;

int main() 
{
	
	SuffixTrie* st = new SuffixTrie("banana$");
	
	test(st->size() == 7);
	test(st->contains("banana$"));
	test(st->contains("anana$"));
	test(st->contains("nana$"));
	test(st->contains("ana$"));
	test(st->contains("na$"));
	test(st->contains("a$"));
	test(st->contains("$"));

	test(!st->contains("ban"));
	test(!st->contains("banana"));

	cout << st->depthLCA;
	//st->printTree();
	delete st;

	st = new SuffixTrie("mississippi$");
	
	test(st->size() == 12);
	
	test(st->contains("mississippi$"));
	test(st->contains("ississippi$"));
	test(st->contains("ssissippi$"));
	test(st->contains("sissippi$"));
	test(st->contains("issippi$"));
	test(st->contains("ssippi$"));
	test(st->contains("sippi$"));
	test(st->contains("ippi$"));
	test(st->contains("ppi$"));
	test(st->contains("pi$"));
	test(st->contains("i$"));
	test(st->contains("$"));

	test(!st->contains("miss"));
	test(!st->contains("mississippi"));

	delete st;

	cout << "Test completed" << endl;

	return 0;
}


