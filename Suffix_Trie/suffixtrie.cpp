#include "suffixtrie.h"
#include <iostream>
using namespace std;

SuffixTrie::SuffixTrie(string s)
{
	int curDepth = 0;
	//longComExt = new string[capacity]; //Hold up to 5 LCEs
	string suffix;
	Node* cur;
	str = s;

	root = new Node(NULL, curDepth);
	//depthLCA = 0;
	
	//Loop counter
	unsigned int i = 0;

	int arrIndex;
	unsigned int j = 0; //counter in loop that parses string into suffixes
	
	//outer loop separates string into suffixes
	for (j = 0; j < str.length(); j++)
	{ 
		curDepth = 1;
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
				cur->child[arrIndex] = new Node(suffix.at(i), curDepth);

			cur = cur->child[arrIndex]; //update node pointer to next child
			curDepth++;
		}
		//Delete this if not needed
		cur->isWord = true; //Set that the last node created completes the added word
	}
	//depthLowestComAncestor(root);
	//longestComExt(root, "");
}

SuffixTrie :: ~SuffixTrie()
{
	// AW: This is a _destructor_
	// It is called when the object "dies" 
	// (either is deleted or goes out of scope)
	// It needs to handle "clean up": deleting any memory allocated
	// using the "new" keyword
	delete_tree(root);

}

void SuffixTrie::delete_tree(Node* cur)
{
	if (cur == 0)
		return;

	for (int i = 0; i < CHARSET; i++)
		delete_tree(cur->child[i]);

	delete cur;
	
}

int SuffixTrie::size()
{
	return size_recursion(root);
}

int SuffixTrie::size_recursion(Node* cur)
{
	//Base case
	if (cur == 0)
		return 0;

	//Inductive case
	int count = 0;

	if (cur->character == '$')
		count++;

	//Returns the word count of children nodes and adds to running total
	for (int i = 0; i < CHARSET; i++)
	{
		count += size_recursion(cur->child[i]);
	}
	return count;
}

bool SuffixTrie::contains(string s)
{
	unsigned int i = 0;
	Node* cur = root;
	int arrIndex;

	if (s.length() == 0)
		return true;

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

int SuffixTrie::LCE(int i, int j)
{
	if (i < 0 || i >= (int)str.length())
		return -1;

	if (j < 0 || j >= (int)str.length())
		return -1;

	return LCE_recursive(root, i, j);
	
	//naive method iterating through string
	//int lengthLCE = 0;

	/*while (i < str.length() && j  < str.length())
	{
		if (str.at(i) != str.at(j))
			break;
			
		lengthLCE++;
		i++;
		j++;
	}
	return lengthLCE;*/
}

//Recursively check if the current character matches at both given indexes
int SuffixTrie::LCE_recursive(Node* cur, int i, int j)
{
	if (cur == 0 || i >= (int)str.length() || i < 0 || j >= (int)str.length() || j < 0)
		return 0;

	int index1;
	int index2;

	index1 = str.at(i) - 97;
	index2 = str.at(j) - 97;

	if (str.at(i) == '$')
		index1 = 26;

	if (str.at(j) == '$')
		index2 = 26;

	if (cur->child[index1] != cur->child[index2])
		return 0;

	return 1 + LCE_recursive(cur->child[index1], i + 1, j + 1);

}

void SuffixTrie::print()
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
	for  (i = 0; i < CHARSET; i++)
		if (cur->child[i] != 0)
		{
			cout << cur->child[i]->character << " " << cur->child[i]->getDepth() << endl;
			print_recursive(cur->child[i]);
		}
}

