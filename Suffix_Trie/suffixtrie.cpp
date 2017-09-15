#include "suffixtrie.h"
#include <iostream>
using namespace std;

SuffixTrie::SuffixTrie(string s)
{
	int curDepth = 0;
	string suffix;
	Node* cur;

	str = s;

	root = new Node(NULL, curDepth);
	
	//Loop counter
	unsigned int i = 0;

	int arrIndex;
	unsigned int j = 0; //counter in loop that parses string into suffixes
	
	//outer loop separates string into suffixes
	for (j = 0; j < str.length(); j++)
	{ 
		curDepth = 1;
		cur = root;
		suffix = str.substr(j, str.length() - j);
		//inner loop adds current suffix to trie
		for (i = 0; i < suffix.length(); i++)
		{
			
			//arrIndex = suffix.at(i) - 97; //map lowercase chars to array indexes
			//
			//if (suffix.at(i) == '$')
			//	arrIndex = 26;

			//Modified for strings defining polyominoes
			arrIndex = char_to_index(suffix.at(i));
			if (arrIndex == -1)
			{
				cout << "Error: invalid input";
				return;
			}



			//if there is no node at array index, add a new node
			if (cur->child[arrIndex] == 0)
				cur->child[arrIndex] = new Node(suffix.at(i), curDepth);

			cur = cur->child[arrIndex]; //update node pointer to next child
			curDepth++;
		}
		//Delete this if not needed
		cur->isWord = true; //Set that the last node created completes the added word
	}
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
	//Modify this to account for strings of multiple versions of boundary word truncated on each other---------------------------------------------------
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
		/*arrIndex = s.at(i) - 97;
		if (s.at(i) == '$')
			arrIndex = 26;*/

		arrIndex = char_to_index(s.at(i));

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

	/*index1 = str.at(i) - 97;
	index2 = str.at(j) - 97;

	if (str.at(i) == '$')
		index1 = 26;

	if (str.at(j) == '$')
		index2 = 26;*/

	index1 = char_to_index(str.at(i));
	index2 = char_to_index(str.at(j));

	//cout << "char at " << i << " is " << str.at(i) << " and is mapped to index " << index1 << endl;
	//cout << "char at " << j << " is " << str.at(j) << " and is mapped to index " << index2 << endl;
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

int SuffixTrie::char_to_index(char c)
{
	c = tolower(c);

	int index;
	switch (c)
	{
		case 'n':
		case 'u':
			index = 0;
			break;

		case 's':
		case 'd':
			index = 1;
			break;

		case 'e':
		case 'r':
			index = 2;
			break;

		case 'w':
		case 'l':
			index = 3;
			break;

		case '!':
			index = 4;
			break;

		case '@':
			index = 5;
			break;

		case '#':
			index = 6;
			break;

		case  '$':
			index = 7;
			break;

		default:
			index = -1;
	}

	return index;
}

string SuffixTrie::reverse_string(string s)
{
	char temp;
	unsigned int i, j;
	for (i = 0; i < s.length()/2; i++)
	{
		j = s.length() - 1 - i;
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
	return s;
}

string SuffixTrie::complement_string(string s)
{
	for (unsigned int i = 0; i < s.length(); i++)
	{
		s[i] = complement(s[i]);
	}
	return s;
}

char SuffixTrie::complement(char c)
{
	switch (c)
	{
	case 'n':
	case 'u':
		return 's';

	case 's':
	case 'd':
		return 'n';
	
	case 'e':
	case 'r':
		return 'w';

	case 'w':
	case 'l':
		return 'e';
	}
}