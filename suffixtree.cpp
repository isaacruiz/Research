#include "suffixtree.h"

SuffixTree::SuffixTree(string s)
{
	for (unsigned int i = 0; i < s.length(); i++) {
		tree.add(s.substr(i, s.length() - i));
	}
}

int SuffixTree::size()
{
	return tree.size();
}

bool SuffixTree::contains(string s)
{
	return tree.contains(s);
}