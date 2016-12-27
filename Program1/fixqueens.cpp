// Margaret He, Jordan Schultz
//queens.cpp

#include "StackAr.h"
#include <iostream>

using namespace std;


StackAr <int> ocp(8); // holds all column positions that are occupied
int board[8][8] = {}; // Initialize the board
bool checkSafety(int r, int c); // function prototype for checking valid moves

int main()
{	  
	board[0][0] = 1; //place the first queen on the board (1 means occupied, 0 means not occupied)
	ocp.push(1);  // Occupy the 1st column
	for(int c = 0; c < 8 ; c++) 
		board[1][c] = 1;	// Occupy the entire row 
		
			
	for (int row = 1; row < 8; row++)	
		for (int col = 0; col < 8; < col++)
	
		bool canoccupy = checkSafety(row, col); //evaluate whether it's safe to place a queen
		if (canoccupy) // if it's safe to add the Queen (the row, column, and diagonal are all not occupied)
		{
			ocp.push(col+1); // add valid column positions to the stack (remember, rows and columns are iterated beginning at 0)
			cout << col+1;
			for(int c = 0; c < 8; c++) 
				board[row][c] = 1; // Occupy the entire row
		else	
			row++;
		}
	}
	
	
	
	while (ocp.isEmpty() == false) // While the occupied column positions' stack is not empty
	{		
		for (int s = 0; s < 8; s++) // s is short for solutions
		{
			cout << ocp.top() << ", ";	// Output all the possible column positions		
			ocp.pop();	
			if (ocp.isEmpty() == true)
			{
				cout << endl;
				break;
			}
		}
	}
	return 0;	
} //end main 



int safe = 0;
int w, x, y, z;
bool checkSafety(int r, int c) // Check if safe to put queen in this row x column position
{
	int safe = 0;
	if (ocp.isFull() == false)// Keep looking for valid columns to place the queens in as long as 8 have not been found yet
	{
		for(int i = 0 ; i < c ; i++)
		{
			if (board[r][i] == 1)//if the row is already occupied
				return (w = 0);
	
			else
				return (w = 1);
		}
		
		for(int j = 0 ; j < r ; j++)
		{
			if(board[j][c] == 1)//if the column is already occupied
				return (x = 0);
				
			else
				return (x = 1);
		}
		
		for (int k = r, l = c ; k >= 0 && l >=0; k--, l--) //if the diagonal is already occupied
		{
			if(board[k][l] == 1)
				return (y = 0);
			
			else
				return (y = 1);
		}
		
		for (int k = r, l = c ; k >=0 && k < 8; k++, l--) // if the other diagonal is already occupied		  
		{
			if(board[k][l] == 1)
				return (z = 0);
				
			else
				return (z = 1);
	
		}
		
		if ((w == x) && (x == y) && (y == z) && (z == 1))
		{
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
	return (safe = 0);
} //end checkSafety definition