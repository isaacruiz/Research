#include "printer.h"

void print(string s)
{
	string corner[] = {"┌─","─┐","└─", "─┘", "┌","┐","└", "┘"};
	string bar[] = {"──","│"};                  
	string intersection[] = {"┼─","─┼", "─┤", "├─", "┴─", "─┴", "┬─", "─┬"};
	string array[20][20];	
	for (int i = 0; i < s.length(); i++)
	{
		for (int j = 0; j < s.length(); j++)
		{
			array [i][j] = " ";
		}
	}

}

