#include "printer.h"

void print(string s)
{
	string c[] = {"┌","┐","└", "┘","─","│","┼"};
	
	string array[20][20];	
	for (int i = 0; i < s.length(); i++)
	{
		for (int j = 0; j < s.length(); j++)
		{
			array [i][j] = " ";
		}
	}
	array[0][2] = c[0];
	for(int i = 3; i < 6; i++)
		array [0][i] = c[4];
	array[0][6] = c[1];	
	array[1][6] = c[6];
	array [2][6] = c[3];
	for(int i = 3; i < 6; i++)
		array[2][i] = c[4];

	array[2][2] = c[2];
	array[1][2] = c[5];
	
	for(int i = 0; i < s.length(); i++){
		for(int j = 0; j < s.length(); j++)
			cout << array[i][j];
		cout << endl;
	}

}
