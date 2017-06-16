#ifndef NODE_H
#define NODE_H

class Node 
{
	public:
		Node* child[26] = {};
		Node* parent;
		char character;
		bool isWord = false;

		Node(Node* p, char c)
		{
			parent = p;
			character = c;
		}
};

#endif
