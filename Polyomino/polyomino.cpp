#include "polyomino.h"
#include <map>

bool isBoundaryWord(string s)
{

}

bool tiles(string s)
{

}

//Test if the path ends where it started
bool enclosed(string s)
{
	int up, down, left, right;
	up = down = left = right = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		switch (s.at(i))
		{
			case 'U':
			case 'u':
				up++;
				break;

			case 'D':
			case 'd':
				down++;
				break;

			case 'L':
			case 'l':
				left++;
				break;

			case 'R':
			case 'r':
				right++;
				break;
		}
	}
	if (left == right && up == down)
		return true;
	
	else
		return false;
}

bool clockwise(string s)
{

}

bool collision(string s)
{

}