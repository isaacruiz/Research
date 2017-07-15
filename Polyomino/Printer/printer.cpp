#include "printer.h"

void print(string s)
{
	string c[] = {"┌","┐","└", "┘","─","│","┼"};
	for(int i = 0; i < 7; i++)
		cout << c[i] << endl;
}
