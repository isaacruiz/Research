#include "suffixtrie.h"
#include <iostream>
using namespace std;

SuffixTrie::SuffixTrie(string s)
{
	root = new Node(' ');
	str = s;

	string suffix;
	Node* cur;

	//Loop counter
	unsigned int i = 0;

	int arrIndex;
	unsigned int j = 0; //counter in loop that parses string into suffixes
	
	//outer loop separates string into suffixes
	for (j = 0; j < str.length(); j++)
	{ 
		cur = root;
		suffix = s.substr(j, str.length() - j);
		
		//inner loop adds current suffix to trie
		for (i = 0; i < suffix.length(); i++)
		{
			arrIndex = suffix.at(i) - 97; //map lowercase chars to array indexes
			if (suffix.at(i) == '$')
				arrIndex = 26;

			//arrIndex = arrayIndex(suffix.at(i));  //maps character to one of 5 indicies

			//if there is no node at array index, add a new node
			if (cur->child[arrIndex] == 0)
				cur->child[arrIndex] = new Node(suffix.at(i));

			cur = cur->child[arrIndex]; //update node pointer to next child
		}

		//Delete this if not needed
		cur->isWord = true; //Set that the last node created completes the added word
	}
	
}

int SuffixTrie::size()
{
		return size_recursion(root);
}

bool SuffixTrie::contains(string s)
{
	unsigned int i = 0;
	Node* cur = root;
	int arrIndex;

	while (i < s.length() && cur != 0)
	{
		//arrIndex = arrayIndex(s.at(i));
		arrIndex = s.at(i) - 97;
		if (s.at(i) == '$')
			arrIndex = 26;

		//if the array element for the current character is empty,
		//then the word is not in the trie
		if (cur->child[arrIndex] == 0)
			return false;

		//Found the current character node, follow its pointer to its 
		//children and look for the next character
		else
			cur = cur->child[arrIndex];
		i++;
	}

	//If the loop exits without returning false, check if current node marks
	//the end of a word and return that value
	return (cur->isWord);
}

string SuffixTrie::longestComExt()
{
	/*
	Lowest node with more than 1 child is the lowest common ancestor. Characters from root to
	lowest common ancestor form the longest common extension
	*/

	//Variable to store depth
	int depth = 0;

	//Varaible to store string that concatenates characters of successive nodes
	string substring;

}

void SuffixTrie::printLowest()
{

}

void SuffixTrie::printTree()
{
	print_recursive(root);

}

void SuffixTrie::print_recursive(Node* cur)
{
	unsigned int i = 0;

	if (cur == 0)
	{
		cout << endl;
		return;
	}

	//Loop through Node* array and print character of each node
	//for (i = 0; i < 5; i++)
	for  (i = 0; i < 27; i++)
		if (cur->child[i] != 0)
		{
			cout << cur->child[i]->character;

			print_recursive(cur->child[i]);
		}
}

int SuffixTrie::size_recursion(Node* cur)
{
	//Base case
	if (cur == 0)
		return 0;

	//Inductive case
	int count = 0;

	if (cur->isWord)
		count++;

	//Returns the word count of children nodes and adds to running total
	//for (int i = 0; i < 5; i++)
	for(int i = 0;  i < 27; i++)
	{
		count += size_recursion(cur->child[i]);
	}

	return count;
}

//Map array index when using 4 cardinal directions
int SuffixTrie::arrayIndex(char c)
{
	switch (c)
	{
	case 'E':
		return 1;

	case 'N':
		return 2;

	case 'S':
		return 3;

	case 'W':
		return 4;

	default:
		return 0;
	}
}

