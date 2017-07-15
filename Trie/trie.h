#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "node.h"

using namespace std;

class Trie 
{
	public:
		Trie();
		void add(string s); //added node* to return address of last node added to tree
		bool contains(string s);
		void del(string s);
		
		void printTrie(Node* cur);
		int size();
		Node* root;

	private:
		
		int noChildren(Node* cur);
		int size_recursion(Node* cur);

};

#endif
