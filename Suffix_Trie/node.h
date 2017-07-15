#ifndef NODE_H
#define NODE_H

const int CHARSET = 27; //Number of different characters that can make up a string

class Node 
{
	public:

		Node* child[CHARSET] = {};
		char character;
		int noChildren = 0;
		bool isWord = false;

		Node(char c, int d)
		{
			character = c;
			depth = d;
		}

		int getDepth()
		{
			return depth;
		}

	private:
		int depth;
};

#endif
