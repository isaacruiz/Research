#ifndef SUFFIXTREE_H
#define SUFFIXTREE_H

#include "trie.h"

class SuffixTree
{
	public:

		SuffixTree(string s);
		int size();
		bool contains(string s);

	private:
		Trie tree;
};

#endif