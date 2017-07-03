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
	SuffixTrie st1("banana$");

	test(st1.size() == 7);

	test(st1.contains("banana$"));
	test(st1.contains("anana$"));
	test(st1.contains("nana$"));
	test(st1.contains("ana$"));
	test(st1.contains("na$"));
	test(st1.contains("a$"));
	test(st1.contains("$"));
	test(st1.contains(""));

	test(!st1.contains("a"));
	test(!st1.contains("ban"));
	test(!st1.contains("banana"));

	test(st1.LCE(1, 3) == 0); // LCE of "anana$" and "ana$" is "ana"	
	test(st1.LCE(0, 3) == 0); // LCE of "banana$" and "ana$" is ""	
	test(st1.LCE(2, 4) == 2); // LCE of "nana$" and "na$" is "na"	
	test(st1.LCE(1, 2) == 0); // LCE of "anana$" and "nana$ is ""
	test(st1.LCE(1, 1) == 6); // LCE of "anana$" and "anana$ is "anana$"
	test(st1.LCE(99, 1) == -1); // Invalid input case: return -1
	test(st1.LCE(99, 99) == -1); // Invalid input case: return -1
	test(st1.LCE(-99, 99) == -1); // Invalid input case: return -1
	test(st1.LCE(-99, -555) == -1); // Invalid input case: return -1


	SuffixTrie st2("mississippi$");
	
	test(st2.size() == 12);
	
	test(st2.contains("mississippi$"));
	test(st2.contains("ississippi$"));
	test(st2.contains("ssissippi$"));
	test(st2.contains("sissippi$"));
	test(st2.contains("issippi$"));
	test(st2.contains("ssippi$"));
	test(st2.contains("sippi$"));
	test(st2.contains("ippi$"));
	test(st2.contains("ppi$"));
	test(st2.contains("pi$"));
	test(st2.contains("i$"));
	test(st2.contains("$"));

	test(!st2.contains("miss"));
	test(!st2.contains("mississippi"));

	test(st2.LCE(1, 4) == 4); // LCE of "ississippi$" and "issippi$" is "issi"
	test(st2.LCE(4, 7) == 1); // LCE of "issippi$" and "ippi$" is "i"
	test(st2.LCE(0, 1) == 0); // LCE of "mississippi$" and "ississippi$" is ""
	test(st2.LCE(2, 2) == 10); // LCE of "ssissippi$" and "ssissippi$" is "ssissippi$"
	

	SuffixTrie st3("abbababaababba$");

	// AW: I like your choice of string.
	// Try to build a set of tests like those above,
	// in particular LCE() calls that return a variety of values.	
	

	cout << "Test completed." << endl;
	return 0;
}


