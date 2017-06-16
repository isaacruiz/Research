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
		char getChar(int, int, int, int);

	private:
		Node* root;
		int noChildren(Node* cur);

};

#endif
