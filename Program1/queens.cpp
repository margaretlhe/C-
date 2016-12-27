// Margaret He, Jordan Schultz
//queens.cpp

#include "StackAr.h"
#include <iostream>

using namespace std;

int main()
{
	bool checkSafety(int c); // function prototype
	StackAr <int> ocp(9); // holds all column positions that are occupied
	
	for (int col = 0; col < 8; col++) //check each column's row
	{
		bool canoccupy = checkSafety(col);
		if (canoccupy == 1) // if it's safe to add the Queen (the row, column, and diagonal are all not occupied)
			ocp.push(col+1); // add valid column positions to the stack
	}
		
	
	
	while (ocp.isEmpty() == false) // While the pcp stack is not empty
	{		
		for (int pcp = 0; pcp < 8; pcp++)
		{
			cout << ocp.top() << ", ";	// Output all the possible column positions		
			ocp.pop();
			
			if (ocp.isEmpty() == true)
				cout << endl;
				break;
		}
	}
	return 0;

}


int safe = 0;
bool checkSafety(int c)
{	
	int board[8][8] = {}; // Initialize the board
	for (int r = 0; r < 8; r++) 
	{
		if ((board[r][c] != r + 1) || (board[r][c] == 0)) // Make sure the row is not occupied
		{
			if ((board[r-1][c-1] != r) && (board[r+1][c-1] != r+2)) // Then make sure the diagonal is not occupied 
			{														// Only look left since the right columns should still be empty
				board[r][c] = r+1; // Occupy this spot on the board and record the row number
				return (safe = 1);
			}
			else
			{
				return (safe = 0);
			}
		}
		
		else
		{
			return (safe = 0);
		}
	}
	
	return (safe = 0);
}