#include "polyomino.h"
#include <map>
#include <iostream>
#include<set>

bool isBoundaryWord(string s)
{
	if (circularWord(s) && clockwise(s) && !collision(s))
		return true;

	else
		return false;
}

bool tiles(string s)
{

}

//Test if the path ends where it started
//Merge into one method with collision to determine at the same time if the path is enclosed and non looping
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

bool clockwise(string s)
{
	char current;
	char next;
	int totalAngle = 0;

	for (size_t i = 0; i < s.length(); i++)
	{
		current = s.at(i);
		next = s.at(i + 1);

		switch (current)
		{
			case 'u':
				if (next == 'r')
					totalAngle += 90;
				if (next == 'l')
					totalAngle -= 90;
				break;

			case 'd':
				if (next == 'l')
					totalAngle += 90;
				if (next == 'r')
					totalAngle -= 90;
				break;

			case 'l':
				if (next == 'u')
					totalAngle += 90;
				if (next == 'd')
					totalAngle -= 90;
				break;

			case 'r':
				if (next == 'd')
					totalAngle += 90;
				if (next == 'u')
					totalAngle -= 90;
				break;
		}
		//cout << totalAngle << endl;
		if (totalAngle > 0)
			return true;

		else
			return false;
	}
}

//Returns true if the boundary word loops back on itself
bool collision(string s)
{
	int x = 0, y = 0;
	
	set<int> coordinates;

	coordinates.insert(100* x + y);
	//cout << "(" << x << ", " << y << ")" << endl;

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
		//cout << "(" << x << ", " << y << ")" << endl;

		if (coordinates.find(100 * x + y) != coordinates.end())
			return true;
		
		else
			coordinates.insert(100 * x + y);
	}

	return false;
}

//string backtrack(string s)
//{
//	string backtrack = "";
//
//	for (size_t i = s.length() - 1; i >= 0; i--)
//	{
//		backtrack += s.at(i);
//		cout << "i: " << i << " " << s.at(i) << endl;;
//	}
//	return backtrack;
//}