#include "polyomino.h"
#include <fstream>

Polyomino::Polyomino(string bw)
{
	boundaryWord = bw;
	
	boundaryLength = bw.length();
	string rc = reverseComplement(bw);
	
	getCoordinates();
	sortCoordinates();

	boundString = bw + bw + rc + rc;
	st = new SuffixTrie(boundString);
	endIndexed = new FactorVector[boundaryLength + 1];
	startIndexed = new FactorVector[boundaryLength + 1];
	midIndexed = new AdmissibleFactor [boundaryLength * 2 + 1];
	getFactors();
	sortFactors();
}

Polyomino::Polyomino()
{

}

Polyomino::~Polyomino()
{

	delete[] coordinates;
	delete[] startIndexed;
	delete[] endIndexed;
	delete[] midIndexed;
	delete st;
}

void Polyomino::getCoordinates()
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

		case 's':
			y++;
			break;

		case 'w':
			x--;
			break;

		case 'e':
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
	if (!isBoundaryWord())
		return false;
	//for every possible six locations
	//iterate over all possible choices of 6 position
	string str = boundaryWord + boundaryWord;

	int posA = 0, lenA = 1, lenB = 1;
	int posB, posC;
	string A, B, C;

	//Iterate over all possible positions of factorizations A B and C
	for (posA = 0; posA < boundaryLength / 2; posA++)
	{
		for (lenA = 1; lenA < boundaryLength / 2; lenA++)
		{
			A = str.substr(posA, lenA);

			if (reverseComplement(A) == str.substr(posA + boundaryLength / 2, lenA))
			{

				for (lenB = 1; lenA + lenB <= boundaryLength / 2; lenB++)
				{
					posB = posA + lenA;
					B = str.substr(posB, lenB);

					if (reverseComplement(B) == str.substr(posB + boundaryLength / 2, lenB))
					{
						if (lenA + lenB == boundaryLength)
							return true;
						else {

							posC = posB + lenB;
							C = str.substr(posC, boundaryLength / 2 - (lenB + lenA));

							if (reverseComplement(C) == str.substr(posC + boundaryLength / 2, boundaryLength / 2 - (lenB + lenA)))
								return true;

						}
					}
				}
			}
		}
	}
	return false;

}

//Loop through ending positions of A in boundary word
//Check the longest A factor with the longest factor of B so that the the sum of lengths is less than or equal to half the boundary length
//Check if there is a corresponding C that totals to half the length of boundary
//If not let A be C and check for the longest B factor that ends right before C starts so that the total length is <=boundaryLength/2
//Then check if there is an A factor that fits into the remaining space to fill half the boundary length
//If neither returns true then increment the position

bool Polyomino::tiles2()
{
	if (!isBoundaryWord())
		return false;

	int si = 0; //index of factor in start-indexed vector  *NOTE - start-indexed lengths increase with increasing index
	int ei = 0; //index of factor in end-indexed vector			  end-indexed lengths decrease with increasing index
	int i;      //index for vector of factors that end at position i
	int r;		//index for vector of factors that start at position r
	//int l;		//index for vector of factors that end at poistion l
	int Clength;
	float ci;	//midpoint index of remaining factor
	for (i = 0; i < boundaryLength/2; i++)
	{
		ei = 0;
		si = 0;

		//move on to next position if there are no factors at index i
		if (endIndexed[i].empty())
			continue;

		//goes through current vector in decreasing lengths
		while (ei < (int)endIndexed[i].size()) 
		{
			r = i + 1;
			if (!startIndexed[r].empty())
			{
				//Finds the next biggest factor that adds to go over boundaryLength/2
				while (endIndexed[i][ei].length + startIndexed[r][si].length <= boundaryLength / 2) 
				{
					si++;
					if (si == startIndexed[r].size()) //Exit loop if the end of vector of factors is reached
						break;
				}
				si--; //Decrement to previous factor to check for a C factor that might complete a BN factorization
				
				if (endIndexed[i][ei].length + startIndexed[r][si].length == boundaryLength / 2)
					return true;

				//Check if there exists a C factorization that completes the consecutive triple
				Clength = boundaryLength / 2 - (endIndexed[i][ei].length + startIndexed[r][si].length);

				//subtract half because even length factors are centered on mid points between indicies
				ci = (float)Clength / 2 - 0.5f + startIndexed[r][si].end + 1; 
				
				 //Check if length of factor at remaining position has the required length to complete factorization
				if (midIndexed[(int)(2 * ci)].length == Clength) 
					return true;
				
			}
			ei++;
		}
	}
	return false;
	/*
	a + b <= n/2
	int bi = 0;

	for (each A that ends at W[i]
	while (B[bi[.length + A.length <=2)
	==Bi;
	--bi;
	int c.start = B.[Bi].end]+1
	int cend = (A.begin + n/2 + n) % n
	//make containers for each start and end point at each position for all admissible factors
	*/
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

//Checks for collisions by looking for duplicate coordinates in sorted coordinate array
bool Polyomino::collision()
{
	
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
	//Sort coordinate array by  y then x
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
	getCoordinates();
}

//void Polyomino::print()
//{
//	int col = maxX - minX;
//	int row = maxY - minY;
//
//	string corner[] = { ┌┐└ ┘ ┌┐└ ┘ };
//	string bar[] = { ─│ };
//	string intersection[] = { ┼ ┤ ├ ┴ ┬};
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
			a.start = start % boundaryLength;
			a.end = end % boundaryLength;
			a.midpoint = (float)(start + end) / 2;
			a.length = end - start + 1;
			a.factor = boundString.substr(start, a.length);
			
			a_hat.start = (a.start + boundaryLength/2) % boundaryLength;
			a_hat.end = (a.end + boundaryLength/2) % boundaryLength;
			a_hat.midpoint = (float)(a_hat.start + a_hat.end) / 2;
			a_hat.length = a.length;
			a_hat.factor = boundString.substr(a_hat.start, a_hat.length);
			
			A.push_back(a);
			A.push_back(a_hat);

		}
	}
}

void Polyomino::sortFactors()
{
	int* counter = new int[boundaryLength] {};
	FactorVector temp = A;
	
	//Sorting by length
	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[temp[i].length]++;
	}

	for (int i = 1; i < boundaryLength; i++)
	{
		counter[i] += counter[i - 1];
	}

	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[temp[i].length]--;
		A[counter[temp[i].length]] = temp[i];
	}

	for (int i = 0; i < boundaryLength; i++)
	{
		counter[i] = 0;
	}

	temp = A;

	sortFactorsByEnd(temp, counter);
	loadLookupVectors();

	delete[] counter;
}

void Polyomino::sortFactorsByEnd(FactorVector &e, int* counter)
{
	FactorVector temp = A;
	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[e[i].end]++;
	}

	for (int i = 1; i < boundaryLength; i++)
	{
		counter[i] += counter[i - 1];
	}

	for (unsigned int i = 0; i < A.size(); i++)
	{
		counter[e[i].end]--;
		A[counter[e[i].end]] = temp[i];
	}
}

//Call this function after sorting factors by length and ending position
void Polyomino::loadLookupVectors()
{
	for (unsigned int i = 0; i < A.size(); i++)
	{
		startIndexed[A[i].start].push_back(A[i]);
		midIndexed[(int)(A[i].midpoint * 2)] = A[i];
		endIndexed[A[i].end].push_back(A[i]);
	}
}

void Polyomino::printFactors()
{
	for (unsigned int i = 0; i < A.size(); i++)
	{
		cout << "Start-End: " << A[i].start << "-" << A[i].end <<  "Length: " << A[i].length << " " << A[i].factor << endl;
	}
}

void Polyomino::printLookupVectors()
{
	cout << "Indexed by starting point:\n";
	for (int i = 0; i < boundaryLength; i++)
	{
		for (unsigned int j = 0; j < startIndexed[i].size(); j++)
			cout << "At [" << i << "][" << j << "] " << startIndexed[i][j].start << " "  << startIndexed[i][j].midpoint <<  " " << startIndexed[i][j].end << "\t\tlength: " << startIndexed[i][j].length << endl;
	}
	cout << "Indexed by end point:\n";
	for (int i = 0; i < boundaryLength; i++)
	{
		for (unsigned int j = 0; j < endIndexed[i].size(); j++)
			cout << "At [" << i << "][" << j << "] " << endIndexed[i][j].start << " "  << endIndexed[i][j].midpoint << " "  << endIndexed[i][j].end <<  "\t\tlength: " << endIndexed[i][j].length << endl;
	}

	cout << "Indexed by midpoint:\n";
	for (int i = 0; i < 2 * boundaryLength; i++)
	{
		if (midIndexed[i].length == 0)
			continue;
		cout << "At [" << i << "]"  << midIndexed[i].start << " " << midIndexed[i].midpoint << " " << midIndexed[i].end << "\t\tlength: " << midIndexed[i].length << endl;
	}
}

void Polyomino::writeLongestFactorPair(ofstream& f)
{
	int maxLength = 0;
	int temp = 0;
	int p = 0;
	int i = 0;
	bool consecutivePair = false;
	AdmissibleFactor A;
	AdmissibleFactor B;
	for (i = 0; i < boundaryLength / 2; i++)
	{
		if (!endIndexed[i].empty() && !startIndexed[i + 1].empty())
		{
			consecutivePair = true;
			A = endIndexed[i][0];
			B = startIndexed[i + 1][startIndexed[i + 1].size() -1];

			temp = A.length + B.length;

			if (temp > maxLength) {
				maxLength = temp;
				p = i;
			}
		}
	}

	f.width(30);
	f << boundaryWord;
		
	f.width(7);
	f << boundaryLength;

	if (consecutivePair)
	{
		A = endIndexed[p][0];  //Reassign A and B to get data of the max length factor pair
		B = startIndexed[p + 1][startIndexed[p + 1].size() - 1];

		f.width(14);
		f << maxLength;


		f.width(16);
		f << A.factor;

		f.width(16);
		f << B.factor;
	}
	else
	{
		f.width(14);
		f << "N/A";

		f.width(16);
		f << "N/A";

		f.width(16);
		f << "N/A";
	}

	f.width(11);
	tiles() ? f << "yes" : f << "no";

	f.width(13);
	tiles2() ? f << "yes" : f << "no";

	f.width(20);
	(tiles() != tiles2()) ? f << "!!!" : f << "";

	f.width(13);
	(maxLength > boundaryLength/2) ? f << "yes": f << "";
	f << endl;
}

void Polyomino::printCoordinates() {
	for (int i = 0; i < boundaryLength; i++) {
		cout << "(" << coordinates[i].x << ", " << coordinates[i].y << ")\n";
	}
}
