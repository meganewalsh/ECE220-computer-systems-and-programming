#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//This program takes an input matrix (or matrices) and creates
//tuples containing the row, col, and value of each cell. It can
//perform addition or multiplication between two matrices, and
//returns the result without tuples containing a value of 0
//(for efficiency). I created several helper functions to help implement
//the setTuples function, and freed the data in memory when the program
//is complete. 

sp_tuples * load_tuples(char* input_file)
{
int num_rows, num_cols, row, col;
double value;
FILE *file;

  sp_tuples *mainTuple = malloc(sizeof(sp_tuples));
  file = fopen(input_file, "r");
//UPDATES SP_TUPLES WITH INFO FROM FILE 
  if(file == NULL)
    return NULL;
  if(fscanf(file, "%d %d ", &num_rows, &num_cols) == 2)
  {
    mainTuple->m = num_rows;
    mainTuple->n = num_cols;
    mainTuple->tuples_head = NULL;
    mainTuple->nz = 0;
  }
  else
  {
    mainTuple->m = 0;
    mainTuple->n = 0;
    mainTuple->tuples_head = NULL;
    mainTuple->nz = 0;
  }

//CALLS SET_TUPLES FOR EACH VALUE IN THE MATRIX
  while(fscanf(file, "%d %d %lf ", &row, &col, &value) == 3)
  {
    set_tuples(mainTuple, row, col, value);
  }
  fclose(file);

//RETURNS A MATRIX OF THE LIST OF TUPLES TYPE
return mainTuple;
}



int overwriteTuple(sp_tuples * mat_t, int row, int col, double value)
{
//This function returns a 1 if a value/node has to be overwritten
//or a 0 if no value needs to be overwritten. If a value/node has
//to be overwritten, this function will do so.
 
  sp_tuples_node *current;
  current = mat_t->tuples_head;

  while(current != NULL)
  {
    if(current->row == row && current->col == col)
    {
      current->value = value;
      return 1;
    }
    current = current->next;
  }
return 0;
}



void createTuple(sp_tuples * mat_t, int row, int col, double value)
{
// This function creates a node for the tuple with the given info.
// It also simultaneously puts the node in the correct spot in the list.
  sp_tuples_node *current, *new, *previous;
//CREATES/FILLS THE NEW NODE
  new = malloc(sizeof(sp_tuples_node));
  
  new->row = row;
  new->col = col;
  new->value = value;
  new->next = NULL;
  previous = NULL;
  current = mat_t->tuples_head;

//Nonzero flag is incremented every time a node is added
//Case: EMPTY LIST
  if(current == NULL)
  {
    mat_t->tuples_head = new;
    mat_t->nz = (mat_t->nz) + 1;
//printt(mat_t);
    return;
  }
  while(current != NULL)
  {
    if(new->row < current->row || (new->row == current->row && new->col <  current->col))
    {
//Case: HEAD NODE
      if(previous == NULL)
      {
        mat_t->tuples_head = new;
        new->next = current;
        mat_t->nz = (mat_t->nz) + 1;
        return;
      }
//Case: NORMAL
      else
      {
        previous->next = new;
        new->next = current;
        mat_t->nz = (mat_t->nz) + 1;
        return;
      }
    }
    if(current->next == NULL)
    {
//Case: TAIL NODE
      current->next = new;
      mat_t->nz = (mat_t->nz) + 1;
      return;
    } 
    previous = current;
    current = current->next;
  }
}



void deleteTuple(sp_tuples * mat_t,int row,int col)
{
double epsilon = 0.000001;
//This function deletes the tuple with given row and col.
//This means that value of this tuple must be equal to 0.
sp_tuples_node *current, *previous = NULL;
  current = mat_t->tuples_head;

//Case: EMPTY LIST - can't remove anything
  if(current == NULL)
    return;

  while(current != NULL)
  {
    if(current->row == row && current->col == col)
    { 
//Case: HEAD NODE
      if(previous == NULL)
      {
        mat_t->tuples_head = current->next;
        if(fabs(current->value) > epsilon)
          mat_t->nz = (mat_t->nz) - 1;
        free(current);
        return; 
      }
//Case: NORMAL & TAIL
      else
      {
        previous->next = current->next;
        if(fabs(current->value) > epsilon)
          mat_t->nz = (mat_t->nz) - 1;
        free(current);
        return;
      }
    }
    previous = current;
    current = current->next;
  }
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
  sp_tuples_node *current;
  current = mat_t->tuples_head;

  while(current != NULL)
  {
    if(current->row == row && current->col == col)
    {
      return current->value;
    }
    current = current->next;
  }  

//Function returns a 0 if tuple does not exist
return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
double epsilon = 0.000001;
//We only care to create tuples for nonzero values
      if(fabs(value) > epsilon)
      {
//If a node can not be overwritten, then it must be created. Never both.
         if(!overwriteTuple(mat_t, row, col, value))
           createTuple(mat_t, row, col, value);
      }
//Value must be 0, which should be deleted
      else
        deleteTuple(mat_t, row, col);
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
int row, col, m, n;
double value;
FILE *file;
  sp_tuples_node *current;
  current = mat_t->tuples_head;
  file = fopen(file_name, "w");

//Print dimensions of the matrix at the top
  m = mat_t->m;
  n = mat_t->n;
  fprintf(file, "%d %d\n", m, n);

//Print the rest of the rows until tail of list is reached  
  while(current != NULL)
  {
    row = current->row;
    col = current->col;
    value = current->value;
      fprintf(file, "%d %d %lf\n", row, col, value);
    current = current->next;
  }
fclose(file);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
int row, col;
double epsilon = 0.000001;
sp_tuples_node *currentA, *currentB, *currentC, *new, *previous = NULL;
//Addition is only possible if matA and matB have the same dimensions
//Addition is impossible - return NULL
  if(matA->m != matB->m || matA->n != matB->n)
    return NULL;
//Addition is possible
  else
  {
//Creates new matrix with same dimensions as matA and matB
    sp_tuples *matC = malloc(sizeof(matA));
//All info about matC is stored
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;
  for(row=0; row < matC->m; row++)
  {
    for(col=0; col < matC->n; col++)
    {
//Creates entries for every row and col in matrix
      new = malloc(sizeof(sp_tuples_node));
//Will create the very first link in the list at head
      if(previous == NULL)
        matC->tuples_head = new;
//Will create all links except the first one
      else
        previous->next = new;
//Fills new struct with information (entries are all 0) 
      new->row = row;
      new->col = col;
      new->value = 0;
      new->next = NULL;
      previous = new;
    }
  }
//Traverse the linked list in matA
    currentA = matA->tuples_head;
    currentC = matC->tuples_head;
    while(currentA != NULL)
    {
      if(fabs(currentA->value) > epsilon)
      {
//Traverse the linked list in matC to find tuple with same row/col
        while(currentC != NULL)
        {
          if(currentC->row == currentA->row && currentC->col == currentA->col)
          {
            currentC->value = currentC->value + currentA->value;
            matC->nz = (matC->nz)+1;
//Change currentC so that we don't check same currentC twice. We can
//do this (without starting back at tuples_head because the list is
//already in order.
            currentC = currentC->next;
            break;  
          }
          currentC = currentC->next;
        }
      }
      currentA = currentA->next;
    }

//SAME THING AS ABOVE BUT USING matB
//Traverse the linked list in matB
    currentB = matB->tuples_head;
    currentC = matC->tuples_head;
    while(currentB != NULL)
    {
      if(fabs(currentB->value) > epsilon)
      {
//Traverse the linked list in matC to find tuple with same row/col
        while(currentC != NULL)
        {
          if(currentC->row == currentB->row && currentC->col == currentB->col)
          {
            if(fabs(currentC->value) < epsilon)
              matC->nz = (matC->nz)+1;
            currentC->value = currentC->value + currentB->value;
            currentC = currentC->next;
            break;  
          }
          currentC = currentC->next;
        }
      }
      currentB = currentB->next;
    }

currentC = matC->tuples_head;
previous = NULL;
//Now clearing out the zeroes
  while(currentC != NULL)
  {
    if(fabs(currentC->value) < epsilon)
    {
      if(currentC == matC->tuples_head)
      {
        matC->tuples_head = currentC->next;
        free(currentC);
        currentC = matC->tuples_head;
      }
      else
      {
        previous->next = currentC->next;
        free(currentC);
        currentC = previous->next;
      }
    }
    else
    {
      previous = currentC;  
      currentC = previous->next;
    }
  }
//Returns matrix with full addition applied 
  return matC;
  }
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{
int row, col;
double epsilon = 0.000001;
sp_tuples_node *currentA, *currentB, *currentC, *new, *previous = NULL;

//Multiplication is only possible when the number of columns
//of matA is equal to the number of rows of matB. 
  if(matA->n != matB->m)
    return NULL;
//Multiplication is possible
  else
  {
//Creates new matrix with same dimensions as matA and matB
    sp_tuples *matC = malloc(sizeof(matA));
//All info about matC is stored
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

  for(row=0; row < matC->m; row++)
  {
    for(col=0; col < matC->n; col++)
    {
//Creates entries for every row and col in matrix
      new = malloc(sizeof(sp_tuples_node));
//Will create the very first link in the list at head
      if(previous == NULL)
        matC->tuples_head = new;
//Will create all links except the first one
      else
        previous->next = new;
//Fills new struct with information (entries are all 0) 
      new->row = row;
      new->col = col;
      new->value = 0;
      new->next = NULL;
      previous = new;
    }
  }

//Traverse the linked list in matA
    currentA = matA->tuples_head;
    //currentC = matC->tuples_head;
    while(currentA != NULL)
    {
      if(fabs(currentA->value) > epsilon)
      {
//Traverse the linked list in matB
        currentB = matB->tuples_head;
        while(currentB != NULL)
        {
//For every non-zero element in B with row iB = jA
          if(fabs(currentB->value) > epsilon && currentB->row == currentA->col)
          {
//Traverse the linked list in matC to find (iA, jB)
            currentC = matC->tuples_head;
            while(currentC != NULL)
            {
              if(currentC->row == currentA->row && currentC->col == currentB->col)
              {
                if(fabs(currentC->value) < epsilon)
                  matC->nz = (matC->nz) + 1;
                currentC->value = currentC->value + currentA->value * currentB->value;
                break;  
              }   
              currentC = currentC->next;
            } 
          }
// Because the structures are all sorted in row major order, you can take advantage of the fact that nodes of the same row will be next to each other when searching matrix B for rows that match.
          if(currentB->row > currentA->col)
            break;
          currentB = currentB->next;
        }
      }
      currentA = currentA->next;
    }

currentC = matC->tuples_head;
previous = NULL;
//Now clearing out the zeroes
  while(currentC != NULL)
  {
    if(fabs(currentC->value) < epsilon)
    {
      if(currentC == matC->tuples_head)
      {
        matC->tuples_head = currentC->next;
        free(currentC);
        currentC = matC->tuples_head;
      }
      else
      {
        previous->next = currentC->next;
        free(currentC);
        currentC = previous->next;
      }
    }
    else
    {
      previous = currentC;  
      currentC = previous->next;
    }
  }

  return matC;
  }
}

	
void destroy_tuples(sp_tuples * mat_t)
{
//Free linked list from left to right
sp_tuples_node *currentC,*previous = NULL;

currentC = mat_t->tuples_head;
//Now clearing out the zeroes
  while(currentC != NULL)
  {
      if(currentC == mat_t->tuples_head)
      {
        mat_t->tuples_head = currentC->next;
        free(currentC);
        currentC = mat_t->tuples_head;
      }
      else
      {
        previous->next = currentC->next;
        free(currentC);
        currentC = previous->next;
      }
  }

//Free matrix
  free(mat_t);
}  
