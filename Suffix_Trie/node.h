#ifndef NODE_H
#define NODE_H

//const int CHARSET = 27; //Number of different characters that can make up a string
const int CHARSET = 8; //4 directions and 4 unique terminating characters
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
