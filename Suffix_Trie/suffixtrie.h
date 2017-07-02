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
		void printTree();
		void depthLowestComAncestor(Node* cur);
		int depthLCA; //Depth of lowest common ancestor
	private:
		
		Node* root;
		Node** terminalChars; //Array to store pointers to leaves
		string str;
		int size_recursion(Node* root);
		void print_recursive(Node* root);
		int arrayIndex(char c);
		
};

#endif