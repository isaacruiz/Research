#include "node.h"
#include <string>
#include "../Polyomino/admissible_factor.h"
#ifndef SUFFIXTRIE_H
#define SUFFIXTRIE_H

using namespace std;



class SuffixTrie
{
	public:
		// Constructor and destructor
		SuffixTrie(string s);
		~SuffixTrie();

		// Returns the number of nodes in the Trie
		int size();

		// Returns whether the trie contains s
		bool contains(string s);

		// Prints the contents of the tree in pre-order 
		void print();

		// Returns the length of the longest common prefix
		// of the substrings of the trie's string that start
		// at indices i and j. 
		int LCE(int i, int j);
		
		string reverse_string(string s);
		string complement_string(string s);
		string str;
	private:
		// Recursive calls for public methods
		int size_recursion(Node* root);
		int LCE_recursive(Node* cur, int i, int j);
		void print_recursive(Node* root);
		void delete_tree(Node* root);
		int char_to_index(char c);
		char complement(char c);
	
		Node* root;
		
};

#endif
