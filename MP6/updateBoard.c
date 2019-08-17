// This program executes the Game of Life, where a 0 represents a dead cell and a 1
// represents a live cell. The physical game board is represented as a 2D array but
// is manipulated in the code as a 1D array. Depending on the number of live neighbors
// of each cell, this algorithm computes whether or not each live/dead cell lives in the next
// generation. The game is over when the board stops changing or when every cell is dead.


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{
int top_edge=0, bottom_edge=0, left_edge=0, right_edge=0;
int alive=0;

// FLAGS ANY EDGES
	if (col == (boardColSize-1))
	   right_edge = 1;
	
	if (col == 0)
	   left_edge = 1;

	if (row == (boardRowSize-1))
	   bottom_edge = 1;

	if (row == 0)
	   top_edge = 1;

// Checks all neighbors
	if (!bottom_edge && board[ (row+1)*boardColSize + col ])			// checks bottom neighbor
	   alive++;
	if (!top_edge && board[ (row-1)*boardColSize + col ])				// checks top neighbor
	   alive++;
	if (!left_edge && board[ row*boardColSize + (col-1) ])				// checks left neighbor
	   alive++;
	if (!right_edge && board[ row*boardColSize + (col+1) ])				// checks right neighbor
	   alive++;
	if (!top_edge && !left_edge && board[ (row-1)*boardColSize + (col-1) ])		// checks top left neighbor
	   alive++;
	if (!top_edge && !right_edge && board[ (row-1)*boardColSize + (col+1) ])	// checks top right neighbor
	   alive++;
	if (!bottom_edge && !left_edge && board[ (row+1)*boardColSize + (col-1) ])	// checks bottom left neighbor
	   alive++;
	if (!bottom_edge && !right_edge && board[ (row+1)*boardColSize + (col+1) ])	// checks bottom right neighbor
	   alive++;
   
   return alive;
}

//-------------------------------------------------------------------------------------
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize)
{
int new_board[(boardRowSize*boardColSize)];								// creates a blank board - same size as original
int row, col, alive_neighbors;

	for(row = 0; row < boardRowSize; row++)
	{ 
	   for(col = 0; col < boardColSize; col++)
	   {
		alive_neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);	// checks neighbors of each cell
   		if (board[ row*boardColSize + col ])							// if target cell is alive, check condition
		{
		   if (alive_neighbors == 2 || alive_neighbors == 3)
		      new_board[ row*boardColSize + col ] = 1;
		   else
		      new_board[ row*boardColSize + col ] = 0;
		}
		else 											// target cell must be dead - check condition
		{											// and store updated value in new board (do not
		    if (alive_neighbors == 3)								// overwrite old board!)
		       new_board[ row*boardColSize + col ] = 1;
		    else
		       new_board[ row*boardColSize + col ] = 0;
		}
	   }
	}

	for(row = 0; row < boardRowSize; row++)
	{ 
	   for(col = 0; col < boardColSize; col++)
	   {
	      board[ row*boardColSize + col ] = new_board[ row*boardColSize + col ];			// take all cell values in new board and
	   }												// transfer back to original board
	}
}
//-----------------------------------------------------------------------------------
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize)
{
int row=0, col=0;
int copy_board[(boardRowSize * boardColSize)];							// empty array/board, same size as original array/board

	   for(row = 0; row < boardRowSize; row++)
	   { 
	      for(col = 0; col < boardColSize; col++)
	      {  
	         copy_board[ row*boardColSize + col ] = board[ row*boardColSize + col ];	// makes a duplicate of the current board
	      }
	   }	
	   updateBoard(copy_board, boardRowSize, boardColSize);					// updates the copy board by calling other function

// Checks if new board equals duplicate old board	
	   for(row = 0; row < boardRowSize; row++)
	   { 
	      for(col = 0; col < boardColSize; col++)
	      {
	         if (board[ row*boardColSize + col] != copy_board[ row*boardColSize + col])	// if they are not equal, change detected
		    return 0;
	      }
	   }

return 1;											// no change detected
}
