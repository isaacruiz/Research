#include "suffixtree.h"
#include <iostream>
using namespace std;

SuffixTree::SuffixTree(string s)
{
	terminalChars = new Node*[s.length()];
	string temp;

	for (unsigned int i = 0; i < s.length(); i++) {
		temp = s.substr(i, s.length() - i);
		
		tree.add(temp, terminalChars[i]); //returns with array element pointing to last character added
		cout << terminalChars[i]->character << endl;
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

void SuffixTree::printTree()
{
	tree.printTrie(root);
}
string SuffixTree::lce()
{
	return "";
}

void SuffixTree::printLowest()
{
	for (int i = 0; i < size(); i++)
		cout << terminalChars[i]->character << endl;
}