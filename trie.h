#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "node.h"

using namespace std;

class Trie 
{
	public:
		Trie();
		void add(string s);
		bool contains(string s);
		void del(string s);
		//TODO add implementation for printing out strings in the trie
		//char getTrie();
		int size();

	private:
		Node* root;
		int noChildren(Node* cur);
		int size_recursion(Node* cur);

};

#endif
