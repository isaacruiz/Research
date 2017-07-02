#ifndef NODE_H
#define NODE_H

class Node 
{
	public:
		//Node* child[5] = {};
		Node* child[27] = {};
		//Node* parent;
		char character;
		bool isWord = false;

		Node(char c)
		{
			character = c;
		}
};

#endif
