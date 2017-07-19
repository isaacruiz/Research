#include "polyomino.h"
#include <map>
#include <iostream>
#include<set>

bool isBoundaryWord(string s)
{
	if (!collision(s) && clockwise(s) && circularWord(s))
		return true;

	else
		return false;
}

bool tiles(string s)
{
	//for every possible six locations
	//iterate over all possible choices of 6 position
	string str = s + s;
	int strlen =(int)s.length();
	int posA = 0, lenA = 1, lenB = 1;
	string A, B, C;

	//Iterate over all possible positions of A
	for (posA = 0; posA < strlen/2; posA++)
	{
		for(lenA = 1; lenA < strlen/2; lenA++)
		{
			A = str.substr(posA, lenA);
			if(reverseComplement(A) == str.substr(posA + strlen/2, lenA))
			{
				for(lenB = 1; lenA + lenB < strlen/2; lenB++)
				{
					B = str.substr(posA + lenA, lenB);
					if(reverseComplement(B) == str.substr(posA + lenA + strlen/2, lenB))
					{
						C = str.substr(posA + lenA + lenB, strlen/2 - lenB);
						if(reverseComplement(C) == str.substr(posA + lenA + lenB + strlen/2, strlen/2 - lenB))
							return true;
					}
				}
			}
		}
	}
	return false;

}

//Test if the path ends where it started
bool circularWord(string s)
{
	int up, down, left, right;
	up = down = left = right = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		switch (s.at(i))
		{
			case 'u':
				up++;
				break;

			case 'd':
				down++;
				break;

			case 'l':
				left++;
				break;
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

//Counts the number of clockwise and counter clockwise turns to
//determine if path traversal is clockwise
bool clockwise(string s)
{
	char current, next;
	int cw = 0, ccw = 0;

	for (size_t i = 0; i < s.length(); i++)
	{
		current = s.at(i);
		
		if (i == s.length() - 1)
			next = s.at(0);
		
		else
			next = s.at(i + 1);

		switch (current)
		{
			case 'u':
				if (next == 'r')
					cw++;
				if (next == 'l')
					ccw++;
				break;

			case 'd':
				if (next == 'l')
					cw++;
				if (next == 'r')
					ccw++;
				break;

			case 'l':
				if (next == 'u')
					cw++;
				if (next == 'd')
					ccw++;
				break;

			case 'r':
				if (next == 'd')
					cw++;
				if (next == 'u')
					ccw++;
				break;
		}
	}

	if (cw > ccw)
		return true;

	else
		return false;
}

//Returns true if the boundary word loops back on itself
bool collision(string s)
{
	int x = 0, y = 0, mul = 100;
	
	set<int> coordinates;

	coordinates.insert(mul* x + y); //Multiply x by mul to ensure "unique" sum
									//(1,0) -> 1   and (0,1) -> 1
									//(1,0) -> 100 and (0,1) -> 1
									//Fails if y coordinate reaches +-mul

	for (size_t i = 0; i < s.length() - 1; i++)
	{
		switch (s.at(i))
		{
			case 'u':
				y++;
				break;

			case 'd':
				y--;
				break;

			case 'l':
				x--;
				break;

			case 'r':
				x++;
				break;
		}

		if (coordinates.find(mul * x + y) != coordinates.end())
			return true;
		
		else
			coordinates.insert(mul * x + y);
	}

	return false;
}

string reverseComplement(string s)
{
	string rc = "";

	for (int i = s.length() - 1; i >= 0; i--)
	{
		switch (s.at(i))
		{
		case 'u':
			rc += 'd';
			break;

		case 'd':
			rc += 'u';
			break;

		case 'l':
			rc += 'r';
			break;

		case 'r':
			rc += 'l';
			break;
		}
	}
	return rc;

}
