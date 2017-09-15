#include "polyomino.h"

Polyomino::Polyomino(string bw)
{
	boundaryWord = bw;
	boundaryLength = bw.length();
	setCoordinates();
	boundString = bw + bw + reverseComplement(bw) + reverseComplement(bw);
	st = new SuffixTrie(boundString);
	getFactors();
}

Polyomino::~Polyomino()
{
	delete[] coordinates;
}

void Polyomino::setCoordinates()
{
	coordinates = new coordinate[boundaryLength];

	//Initialize coordinate array
	int x = 0, y = 0;
	for (int i = 0; i < boundaryLength; i++)
	{

		switch (boundaryWord.at(i))
		{
		case 'n':
			y--;
			break;

		case 'd':
			y++;
			break;

		case 'l':
			x--;
			break;

		case 'r':
			x++;
			break;
		}

		if (x < minX)
			minX = x;
		if (x > maxX)
			maxX = x;
		if (y < minY)
			minY = y;
		if (y > maxY)
			maxY = y;

		coordinates[i].x = x;
		coordinates[i].y = y;
	}
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
	for (posA = 0; posA < boundaryLength/2; posA++)
	{
		for(lenA = 1; lenA < boundaryLength/2; lenA++)
		{
			A = str.substr(posA, lenA);
//			cout << "checking posA: " << posA << "  A: " << setw(15) << left << A <<"A_rc: " << setw(15) << left << reverseComplement(A)
//				<< "Acomp: " << str.substr(posA + boundaryLength / 2, lenA) << endl;
			if(reverseComplement(A) == str.substr(posA + boundaryLength/2, lenA))
			{
//				cout << endl;

				for(lenB = 1; lenA + lenB <= boundaryLength/2; lenB++)
				{
					posB = posA + lenA;
					B = str.substr(posB, lenB);
//					cout << "checking posB: " << posB << "  B: " << setw(15) << B << "B_rc: " << setw(15) << left << reverseComplement(B)
//						<< "Bcomp: " << str.substr(posB + boundaryLength / 2, lenB) << endl;
					if(reverseComplement(B) == str.substr(posB + boundaryLength/2, lenB))
					{
						if (lenA + lenB == boundaryLength)
							return true;
						else {
//							cout << endl;
							posC = posB + lenB;
							C = str.substr(posC, boundaryLength / 2 - (lenB + lenA));
//							cout << "checking posC: " << posC << "  C: " << setw(15) << C << "C_rc: " << setw(15) << left << reverseComplement(C)
//								<< "Ccomp: " << str.substr(posC + boundaryLength / 2, lenB) << endl;
							if (reverseComplement(C) == str.substr(posC + boundaryLength / 2, boundaryLength / 2 - (lenB + lenA)))
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
	for (int i = 0; i < boundaryLength; i++)
	{
		switch (boundaryWord.at(i))
		{
			case 'n':
				up++;
				break;

			case 's':
				down++;
				break;

			case 'w':
				left++;
				break;
			case 'e':
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

	for (int i = 0; i < boundaryLength; i++)
	{
		current = boundaryWord.at(i);
		
		if (i == boundaryLength - 1)
			next = boundaryWord.at(0);
		
		else
			next = boundaryWord.at(i + 1);

		switch (current)
		{
			case 'n':
				if (next == 'e')
					cw++;
				if (next == 'w')
					ccw++;
				break;

			case 's':
				if (next == 'w')
					cw++;
				if (next == 'e')
					ccw++;
				break;

			case 'w':
				if (next == 'n')
					cw++;
				if (next == 's')
					ccw++;
				break;

			case 'e':
				if (next == 's')
					cw++;
				if (next == 'n')
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
//bool Polyomino::collision()
//{
//	int x = 0, y = 0, mul = boundaryLength;
//	
//	set<int> coordinates;
//
//	coordinates.insert(mul* x + y); //Multiply x by mul to ensure "unique" sum
//									//(1,0) -> 1   and (0,1) -> 1
//									//(1,0) -> 100 and (0,1) -> 1
//									//Fails if y coordinate reaches +-mul
//
//	for (size_t i = 0; i < boundaryLength - 1; i++)
//	{
//		switch (boundaryWord.at(i))
//		{
//			case 'n':
//				y++;
//				break;
//
//			case 'd':
//				y--;
//				break;
//
//			case 'l':
//				x--;
//				break;
//
//			case 'r':
//				x++;
//				break;
//		}
//
//		if (coordinates.find(mul * x + y) != coordinates.end())
//			return true;
//		
//		else
//			coordinates.insert(mul * x + y);
//	}
//
//	return false;
//}

//Checks for collisions with radix sort
bool Polyomino::collision()
{
	sortCoordinates();
	for (int i = 0; i < boundaryLength - 1; i++)
	{
		if (coordinates[i].y == coordinates[i + 1].y && coordinates[i].x == coordinates[i + 1].x)
				return true;
	}

	return false;
}

//Redelmeier's algorithm
//Add code to measure running time
void Polyomino::sortCoordinates()
{
	//Sort coordinate array by  y, then x
	int range;
	int* offset;
	int* counter;
	int n;

	coordinate* tempCoord = new coordinate[boundaryLength];

	//Shifts array indexes to account for negative numbers
	range = maxY - minY;
	counter = new int[range + 1]();
	offset = &counter[0 - minY];

	for (int i = 0; i < boundaryLength; i++)
		offset[coordinates[i].y]++;

	for (int i = 1; i < range + 1; i++)
		counter[i] = counter[i] + counter[i - 1];

	for (int i = boundaryLength - 1; i >= 0; i--)
	{
		n = --offset[coordinates[i].y];
		tempCoord[n] = coordinates[i];
	}

	delete[] coordinates;
	delete[] counter;

	coordinates = tempCoord;

	//Sort by X coordinate
	tempCoord = new coordinate[boundaryLength];

	//Shifts array indexes to account for negative numbers
	range = maxX - minX;
	counter = new int[range + 1]();
	offset = &counter[0 - minX];

	for (int i = 0; i < boundaryLength; i++)
		offset[coordinates[i].x]++;

	for (int i = 1; i < range + 1; i++)
		counter[i] = counter[i] + counter[i - 1];

	for (int i = boundaryLength - 1; i >= 0; i--)
	{
		n = --offset[coordinates[i].x];
		tempCoord[n] = coordinates[i];
	}

	delete[] coordinates;
	delete[] counter;

	coordinates = tempCoord;
}

string Polyomino::reverseComplement(string s)
{
	string rc = "";

	for (int i = s.length() - 1; i >= 0; i--)
	{
		switch (s.at(i))
		{
		case 'n':
			rc += 's';
			break;

		case 's':
			rc += 'n';
			break;

		case 'w':
			rc += 'e';
			break;

		case 'e':
			rc += 'w';
			break;
		}
	}
	return rc;
}

void Polyomino::scale(int n)
{
	size_t i = 0;
	int j, k;
	while (i < boundaryWord.length())
	{
		boundaryWord.insert(i, n - 1, boundaryWord.at(i));
		i += n;
	}
	j = rand() % boundaryWord.length();
	k = boundaryWord.length() - j;
	
	boundaryWord = boundaryWord.substr(j, k) + boundaryWord.substr(0, j); //makes boundary word start at random point
	boundaryLength = boundaryWord.length();
	delete[] coordinates;
	setCoordinates();
}

//void Polyomino::print()
//{
//	int col = maxX - minX;
//	int row = maxY - minY;
//
//	string corner[] = { "┌","┐","└", "┘", "┌","┐","└", "┘" };
//	string bar[] = { "─","│" };
//	string intersection[] = { "┼", "┤", "├", "┴", "┬"};
//	string** board = new string*[col];
//	string** offset;
//
//}

int Polyomino::indexOfComplement(int x)
{
	int i = 2 * boundaryLength - 1 - x;
	while (i < x)
		i += boundaryLength;

	i += 2 * boundaryLength - boundaryLength/2;

	//cout << "Complement index of " << x << " is " << i << " with a character of " << boundString.at(i) << endl;
	return i;
}

void Polyomino::getFactors()
{
	AdmissibleFactor a, a_hat;
	int j = boundaryLength / 2;
	int start, end;
	int rightExtensionLength, leftExtensionLength;
	int pos;
	for (int i = boundaryLength; i < 2 * boundaryLength; i++)
	{
		pos = i / 2;
		if (i % 2 != 0)  //To do halfstep LCE queries between character positions
		{
		
			//cout << "position: " << pos << ".5 position of complement: " << indexOfComplement(pos + j) << endl;
			rightExtensionLength = st->LCE(pos + 1, indexOfComplement(pos));
			leftExtensionLength = st->LCE(pos + j + 1, indexOfComplement(pos + j));
			start = pos - leftExtensionLength + 1;
			end = pos + rightExtensionLength;
		}

		else
		{
			rightExtensionLength = st->LCE(pos, indexOfComplement(pos));
			leftExtensionLength = st->LCE(pos + j, indexOfComplement(pos + j));
			start = pos - (leftExtensionLength - 1);
			end = pos + (rightExtensionLength - 1);
		}

		if (rightExtensionLength == leftExtensionLength && rightExtensionLength != 0)
		{
			//cout << "adding factor " << start << "-" << end << " from position " << pos << endl;
			a.start = start % boundaryLength;
			a.end = end % boundaryLength;
			a.length = end - start + 1;

			a_hat.start = (a.start + boundaryLength/2) % boundaryLength;
			a_hat.end = (a.end + boundaryLength/2) % boundaryLength;
			a_hat.length = a.length;
			
			A.push_back(a);
			A.push_back(a_hat);
		}
	}
}

void Polyomino::sortFactors()
{
	int* counter = new int[boundaryLength] {};
	vector <AdmissibleFactor> temp = A;
	
	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[temp[i].length]++;
	}

	for (unsigned int i = 1; i < boundaryLength; i++)
	{
		counter[i] += counter[i - 1];
	}

	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[temp[i].length]--;
		A[counter[temp[i].length]] = temp[i];
	}

	for (unsigned int i = 0; i < boundaryLength; i++)
	{
		counter[i] = 0;
	}

	temp = A;

	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[temp[i].start]++;
	}

	for (unsigned int i = 1; i < boundaryLength; i++)
	{
		counter[i] += counter[i - 1];
	}

	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[temp[i].start]--;
		A[counter[temp[i].start]] = temp[i];
	}



	delete[] counter;

}

void Polyomino::printFactors()
{
	for (unsigned int i = 0; i < A.size(); i++)
	{
		cout << "Start-End: " << A[i].start << "-" << A[i].end << " Length: " << A[i].length << endl;
	}
}