#include "polyomino.h"
#include <map>
#include <iostream>
#include <iomanip>
#include<set>

Polyomino::Polyomino(string bw)
{
	boundaryWord = bw;
	wordLength = bw.length();
}

bool Polyomino::isBoundaryWord()
{
	if (!collision() && clockwise() && circularWord())
		return true;

	else
		return false;
}

bool Polyomino::tiles()
{
	//for every possible six locations
	//iterate over all possible choices of 6 position
	string str = boundaryWord + boundaryWord;

	int posA = 0, lenA = 1, lenB = 1;
	int posB, posC;
	string A, B, C;

	//Iterate over all possible positions of factorizations A, B, and C
	for (posA = 0; posA < wordLength/2; posA++)
	{
		for(lenA = 1; lenA < wordLength/2; lenA++)
		{
			A = str.substr(posA, lenA);
//			cout << "checking posA: " << posA << "  A: " << setw(15) << left << A <<"A_rc: " << setw(15) << left << reverseComplement(A)
//				<< "Acomp: " << str.substr(posA + wordLength / 2, lenA) << endl;
			if(reverseComplement(A) == str.substr(posA + wordLength/2, lenA))
			{
//				cout << endl;

				for(lenB = 1; lenA + lenB <= wordLength/2; lenB++)
				{
					posB = posA + lenA;
					B = str.substr(posB, lenB);
//					cout << "checking posB: " << posB << "  B: " << setw(15) << B << "B_rc: " << setw(15) << left << reverseComplement(B)
//						<< "Bcomp: " << str.substr(posB + wordLength / 2, lenB) << endl;
					if(reverseComplement(B) == str.substr(posB + wordLength/2, lenB))
					{
						if (lenA + lenB == wordLength)
							return true;
						else {
//							cout << endl;
							posC = posB + lenB;
							C = str.substr(posC, wordLength / 2 - (lenB + lenA));
//							cout << "checking posC: " << posC << "  C: " << setw(15) << C << "C_rc: " << setw(15) << left << reverseComplement(C)
//								<< "Ccomp: " << str.substr(posC + wordLength / 2, lenB) << endl;
							if (reverseComplement(C) == str.substr(posC + wordLength / 2, wordLength / 2 - (lenB + lenA)))
								return true;
//							cout << endl;
						}
					}
				}
			}
		}
	}
	return false;

}

//Test if the path ends where it started
bool Polyomino::circularWord()
{
	int up, down, left, right;
	up = down = left = right = 0;
	for (int i = 0; i < wordLength; i++)
	{
		switch (boundaryWord.at(i))
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
bool Polyomino::clockwise()
{
	char current, next;
	int cw = 0, ccw = 0;

	for (int i = 0; i < wordLength; i++)
	{
		current = boundaryWord.at(i);
		
		if (i == wordLength - 1)
			next = boundaryWord.at(0);
		
		else
			next = boundaryWord.at(i + 1);

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
bool Polyomino::collision()
{
	int x = 0, y = 0, mul = wordLength;
	
	set<int> coordinates;

	coordinates.insert(mul* x + y); //Multiply x by mul to ensure "unique" sum
									//(1,0) -> 1   and (0,1) -> 1
									//(1,0) -> 100 and (0,1) -> 1
									//Fails if y coordinate reaches +-mul

	for (size_t i = 0; i < wordLength - 1; i++)
	{
		switch (boundaryWord.at(i))
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

//Checks for collisions with radix sort
//bool Polyomino::collision(string s)
//{
//
//	
//	int x = 0, y = 0;
//	int minX = x, minY = y;
//	int maxX = x, maxY = y;
//
//	coordinate* coord = new coordinate[s.length()];
//	
//	for (int i = 0; i < s.length(); i++)
//	{
//
//		switch (s.at(i))
//			{
//			case 'u':
//				y--;
//				break;
//
//			case 'd':
//				y++;
//				break;
//
//			case 'l':
//				x--;
//				break;
//
//			case 'r':
//				x++;
//				break;
//			}
//
//		if (x < minX)
//			minX = x;
//		if (x > maxX)
//			maxX = x;
//		if (y < minY)
//			minY = y;
//		if (x > maxY)
//			maxY = y;
//
//		coord[i].x = x;
//		coord[i].y = y;
//	}
//
//	//Sort coordinate array by  x, then y
//
//}

void Polyomino::radixSort(int **arr)
{

}
string Polyomino::reverseComplement(string s)
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
