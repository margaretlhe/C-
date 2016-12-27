#include <stdio.h>
#include "StackAr.h"
#include <iostream>

bool checkSafe(bool board[8][8], int row, int column);
using namespace std;

int main()
{
    int row = 0, column = 0 , placedqueens = 0;
    StackAr <int> queen_columns(90); //provide one element worth of leeway
    bool board[8][8];
    for(int i = 0; i < 8 ; ++i) //declare entire board false to begin
        for(int k = 0 ; k < 8; ++k)
            board[i][k] = false;
    
    board[0][0] = true; //place the first queen on the board
    queen_columns.push(column + 1); //add the first column into the occupied column positions
    placedqueens++;
    row++;
    
	
    while(placedqueens !=8) 
	{
       if (checkSafe(board, row, column)) // if the board is safe to place a queen there
       {         
			queen_columns.push(column);
            board[row][column] = true;
			row++;
            placedqueens++;
        } 
       
	   if ((column > 7 && placedqueens != 8) && (queen_columns.isEmpty() == false))
		{
				queen_columns.pop();
				placedqueens--;
				board[row][column] = false;
		}
		
		else if (!checkSafe(board, row, column))//if the board isn't safe to place a queen there
		{ 
            column++;
        }
	}
	
	while (queen_columns.isEmpty() == false) //while the queen column stack is not empty
	{
		for (int i = 0; i < 8; i++)
		{
			cout << queen_columns.topAndPop() << ", ";  //output all the column numbers
			if (queen_columns.isEmpty() == true) // after you have output all the column numbers, break from the loop
				cout << endl;
				break;
		}
	}

    return 0;

}//end main

bool checkSafe(bool board[8][8], int row, int column)
{
    for(int i = 0 ; i < column ; i++)
        if(board[row][i] == true)//if in the same row
            return false;

    for(int j = 0 ; j < row ; j++)
        if(board[j][column] == true)//if in the same column
            return false;
   
    for(int k = row, l = column ; k >=0 && l >=0; k--, l--)
      if(board[k][l] == true)
        return false;
    
    for(int k = row, l = column ; k >=0 && k < 8; k++, l--)
      if(board[k][l] == true)
        return false;
	
	return true;
}