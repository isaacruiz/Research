
#include "trie.h"
#include <iostream>

Trie::Trie()
{
	root = new Node(0, ' ');
}

void Trie::add(string s)
{
	Node* cur = root;
	
	//Loop counter
	unsigned int i = 0;
	
	int arrIndex;
	
	while (i < s.length())
	{
		arrIndex = s.at(i) - 97; //map lowercase chars to array indexes

		//if there is no node at array index, add a new node
		if (cur->child[arrIndex] == 0)
			cur->child[arrIndex] = new Node(cur, s.at(i));

		cur = cur->child[arrIndex]; //update node pointer to next child
		i++;

	}
	cur->isWord = true; //Set that the last node created completes the added word
}

char Trie::getChar(int a, int b, int c, int d) {


	return root->child[a]->child[b]->child[c] -> child[d]->character;
}
bool Trie::contains(string s)
{
	unsigned int i = 0;
	Node* cur = root;
	int arrIndex;

	while (i < s.length() && cur != 0) {
		arrIndex = s.at(i) - 97;

		//if the array element for the current character is empty, then the word is not in the trie
		if (cur->child[arrIndex] == 0)
			return false;

		//Found the current character node, follow its pointer to its children and look for the next character
		else
			cur = cur->child[arrIndex];
		i++;
	}
	
	//If the loop exits without returning false, check if current node marks the end of a word and return that value
	return (cur->isWord);
}

void Trie::del(string s)
{
	if (!contains(s)) {
		cout << s + " was not found in dictionary\n\n";
		return;
	}

	Node* cur = root;

	//Loop counter
	unsigned int i = 0;

	int arrIndex;

	//Traverse down the trie until reaching the last node of the word
	while (i < s.length())
	{
		arrIndex = s.at(i) - 97; //map lowercase chars to array indexes
		cur = cur->child[arrIndex]; //update node pointer to next child
		i++;
	}

	//If the last node of the string has a child, mark its isWord variable as
	//false to "delete" the word
	if (noChildren(cur) >= 1) {
		cur->isWord = false;
		return;
	}
	else {
		
		//traverse back up the list, deleting child nodes until a node is reached that
		//has multiple children or reach a node that completes a substring of the current
		//word being deleted
		
		for (i = (s.length() - 1); i >= 0; i--) {
			arrIndex = s.at(i) - 97;
			cur = cur->parent;
			
			if (noChildren(cur->child[arrIndex]) == 0) {
				delete cur->child[arrIndex];
				cur->child[arrIndex] = 0;

			if (cur->isWord == true)//Stop deleting nodes when reaching a substring of current word that is in trie
				return;

			
			}
		}
	}
}

int Trie::noChildren(Node* cur) {
	
	int noChildren = 0;
	for (int i = 0; i < 26; i++) {
		if (cur->child[i] != 0)
			noChildren++;
	}

	return noChildren;
}

