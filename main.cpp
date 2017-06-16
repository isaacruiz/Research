#include <iostream>
#include "trie.h"

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file << ", line " << line << "." << endl;
        abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


using namespace std;
int main() {
	
	Trie trie;
	trie.add("a");
	trie.add("arc");
	trie.add("area");
	trie.add("army");
	trie.add("armies");
	trie.add("ant");
	trie.add("zero");
	trie.add("zoo");
	trie.add("ante");

	test(trie.contains("a"));
	test(trie.contains("arc"));
	test(trie.contains("area"));
	test(trie.contains("army"));
	test(trie.contains("armies"));
	test(trie.contains("ant"));
	test(trie.contains("ante"));
	test(trie.contains("zero"));
	test(trie.contains("zoo"));

	test(!trie.contains("are"));
	test(!trie.contains("an"));
	test(!trie.contains("arm"));

	trie.add("are");
	trie.add("arm");
	trie.add("an");

	test(trie.contains("are"));
	test(trie.contains("an"));
	test(trie.contains("arm"));

	trie.del("area");
	test(trie.contains("arc"));
	test(trie.contains("ant"));
	test(!trie.contains("area"));

	cout << "Testing complete." << endl;

	return 0;
}


