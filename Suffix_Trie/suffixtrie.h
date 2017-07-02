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
		void longestComExt(Node* cur, string s);
		void printTree();
		void depthLowestComAncestor(Node* cur);
		int depthLCA; //Depth of lowest common ancestor
		void printLCE();
		
	private:
		
		Node* root;
		string str;
		string* longComExt;
		int size_recursion(Node* root);
		void print_recursive(Node* root);
		int arrayIndex(char c);
		int capacity = 5; //Array cap for number of LCEs
		
};

#endif