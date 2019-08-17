#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//This program reads a maze from an input file (including the dimensions) and
//returns the same maze outline but filled with the solution to the maze represented
//by a dotted line "....". It can do this through the application of recursion,
//structures, and malloc. For each cell, the program checks the cell to the left of it,
//the cell below it, the cell to the right of it, and then the cell above it in that
//order. When the maze is returned, the "~~~~" line represents the paths that were
//attempted but that failed to reach the end. If the input maze is unsolvable, it will
//say so.

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
// Your code here. Make sure to replace following line with your own code.
int num_rows=0, num_cols=0, row, col, cntr;
char simple_char;
FILE *file;

//Dynamically allocates memory for game
   maze_t * mymaze = malloc(sizeof(maze_t));

//Gets dimensions of maze
  file = fopen(fileName, "r");
if(file != NULL && fscanf(file, "%d %d ", &num_rows, &num_cols) == 2)
{
//Dynamically allocates memory for game
  mymaze->cells = malloc(sizeof(char *)*num_rows);
  for(cntr = 0; cntr < num_rows; cntr++)
      mymaze->cells[cntr] = malloc(sizeof(char)*num_cols);

//Initializes cells in maze array, read from file   
  for(row=0; row<num_rows; row++)
  {
    for(col=0; col<num_cols; col++)
    {
      fscanf(file, "%c", &simple_char);
      mymaze->cells[row][col] = simple_char;
      if(mymaze->cells[row][col] == 'S')
      {
      //Finds the Start & saves its location in structure
         mymaze->startColumn = col;
         mymaze->startRow = row;
      }
      if(mymaze->cells[row][col] == 'E')
      {
      //Finds the End & saves its location in structure
         mymaze->endColumn = col;
         mymaze->endRow = row;
      }
    }
    //Discards the new line after every row
    fscanf(file, "%c", &simple_char);
  }
  fclose(file);

//Initializes other variables - width, height
   mymaze->height = num_rows;
   mymaze->width = num_cols;

}
//Returns a filled maze structure with contents from file
return mymaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
int j;
   for(j=0; j<maze->height; j++)
      free(maze->cells[j]);
   free(maze->cells);
   
   free(maze);
   maze = NULL;
   return;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
int row, col;
   for(row = 0; row < maze->height; row++)
   {
      for(col = 0; col < maze->width; col++)
      {
            printf("%c", maze->cells[row][col]);
      }
   //Prints the new line after every row
   printf("\n");
   }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
// Your code here.

static int first_call = 0;
first_call++;

//Checking base cases - boundaries of maze.   
   if(row >= maze->height || row < 0 || col >= maze->width || col < 0)
      return 0;
  
   if(maze->cells[row][col] != ' ' && !(first_call == 1 && maze->cells[row][col] == 'S') && maze->cells[row][col] != 'E')
       return 0;	

   if(maze->cells[row][col] == 'E')
   {
//      maze->cells[maze->startRow][maze->startColumn] = 'S';
      return 1;
   }

//Cell was visited and is part of solution.   
   if(maze->cells[row][col] != 'S')
      maze->cells[row][col] = '.';

//Checking all sides...   
   if(solveMazeManhattanDFS(maze, col-1, row)) //left
      return 1;
   if(solveMazeManhattanDFS(maze, col, row+1)) //down
      return 1;
   if(solveMazeManhattanDFS(maze, col+1, row)) //right
      return 1;
   if(solveMazeManhattanDFS(maze, col, row-1)) //up
      return 1;

//Cell was visited and is not part of solution.   
   if(maze->cells[row][col] != 'S')
      maze->cells[row][col] = '~';

return 0;
}
