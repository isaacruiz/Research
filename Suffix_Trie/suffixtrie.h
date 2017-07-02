#include "node.h"
#include <string>

#ifndef SUFFIXTRIE_H
#define SUFFIXTRIE_H

using namespace std;

class SuffixTrie
{
	public:

		SuffixTrie(string s);
		int size();
		bool contains(string s);
		string longestComExt();
		void printLowest();
		void printTree();

	private:
		Node* root;
		Node** terminalChars;
		string str;
		int size_recursion(Node* root);
		void print_recursive(Node* root);
		int arrayIndex(char c);
};

#endif