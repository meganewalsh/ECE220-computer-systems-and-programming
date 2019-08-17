// This program takes a standard sudoku board and solves it through the
// application of recursion. For each cell, the attempted input val
// must be the only val in that row, in that column, and in that 3x3
// grid. As long as this is true, the program will contine solving
// the board (through recursion) until it either 1) is completely solved
// or 2) it is not completely solved and cannot be solved any further. If
// this is the case, the program backtracks and tries again with a
// different val until the board is finally completely filled.


#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) 
{
int col;
	assert(i>=0 && i<9);
	   for (col = 0; col < 9; col++)	// iterates through each column in given row
	   {   
	      if (sudoku[i][col] == val)	// checks every cell for val
	      return 1;
	   }
return 0;					// will return 0 if value can exist in row
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) 
{
int row;
	assert(j>=0 && j<9);
	   for (row = 0; row < 9; row++)	// iterates through each row in given col
	   {   
	      if (sudoku[row][j] == val)	// checks every cell for val
	      return 1;
	   }
return 0;					// will return 0 if value can exist in col
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
int row, col;
int row_start, row_end, col_start, col_end;

	assert(i>=0 && i<9);
	assert(j>=0 && j<9);				// not given but necessary

// The following if statements determine which 3x3 grid the given cell is located in. Gives the bounds of that grid.
	if(i >= 0 && i < 3)				// cell located in top three rows?
	{
	   row_start = 0;
	   row_end = 2;
	}
	else if(i >= 3 && i < 6)			// cell located in middle three rows?
	{
	   row_start = 3;
	   row_end = 5;
	}
	else if(i >= 6 && i < 9)			// cell located in last three rows?
	{
	   row_start = 6;
	   row_end = 8;
	}
	
	if(j >= 0 && j < 3)				// cell located in first three cols?
	{
	   col_start = 0;
	   col_end = 2;
	}
	else if(j >= 3 && j < 6)			// cell located in middle three cols?
	{
	   col_start = 3;
	   col_end = 5;
	}
	else if(j >= 6 && j < 9)			// cell located in last three cols?
	{
	   col_start = 6;
	   col_end = 8;
	}

// Location of 3x3 grid is known. Checks all cells in that grid for the given value. 
	for(row = row_start; row <= row_end; row++)
	{
	   for(col = col_start; col <= col_end; col++)
	   {
	      if(sudoku[row][col] == val)
	         return 1;
	   }
	}

return 0;						// will return 0 if value can exist in 3x3 grid.
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) 
{
int return_val;
	assert(i>=0 && i<9 && j>=0 && j<9);

//  Value will only be valid if it passes previous three functions.	
	return_val = is_val_in_row(val, i, sudoku);
	if (return_val == 1)
	   return 0; 
	
	return_val = is_val_in_col(val, j, sudoku);
	if (return_val == 1)
	   return 0; 

	return_val = is_val_in_3x3_zone(val, i, j, sudoku);
	if (return_val == 1)
	   return 0; 

return 1;						// If all functions return a zero this function returns a 1,
}							// that the value can exist in the given entry.

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) 
{
int return_val, all_cells_filled;
int row, col;
	   all_cells_filled = 1;
	   for(row = 0; row < 9; row++)
	   {
	      for(col = 0; col < 9; col++)
	      {   
		 if(sudoku[row][col] == 0)
		 {
		    all_cells_filled = 0;
		    break;						// stop once a zero is detected. A zero means 
		 }							// that all cells must not be filled.
	      }
	      if(all_cells_filled == 0)
		break;							// break out of both for loops in order to
	   }								// save the [row][col] which contains a 0

	   if(all_cells_filled == 1)
	      return 1;

	   for(int num = 1; num <= 9; num++)				// num represent the value we are trying to fill
	   {								// into the empty cell
	      return_val = is_val_valid(num, row, col, sudoku);		// find a value that is valid (passes all tests)
	      if(return_val == 1)
	      {
	         sudoku[row][col] = num;
	         if(solve_sudoku(sudoku))				// recursion
		    return 1;
	         sudoku[row][col] = 0;  				// if can't be solved with num, reset to 0
	      }
	   }
return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





