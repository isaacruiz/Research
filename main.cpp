#include <iostream>
#include "trie.h"
#include <cassert>

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

	assert(trie.contains("a") == true);
	assert(trie.contains("arc") == true);
	assert(trie.contains("area") == true);
	assert(trie.contains("army") == true);
	assert(trie.contains("armies") == true);
	assert(trie.contains("ant") == true);
	assert(trie.contains("ante") == true);
	assert(trie.contains("zero") == true);
	assert(trie.contains("zoo") == true);

	assert(trie.contains("are") == false);
	assert(trie.contains("an") == false);
	assert(trie.contains("arm") == false);

	trie.add("are");
	trie.add("arm");
	trie.add("an");

	assert(trie.contains("are") == true);
	assert(trie.contains("an") == true);
	assert(trie.contains("arm") == true);

	trie.del("area");
	assert(trie.contains("arc") == true);
	assert(trie.contains("ant") == true);
	assert(trie.contains("area") == false);
	
	return 0;

}
