// When given a valid input seed, this program generates four random
// numbers between 1 & 8 and gives the user 12 guesses to type in
// the correct combination. The program tells the user how many values
// were correct or misplaced each time. Once the combination is
// guessed correctly, the game/program ends. 




/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below

int check_int;
int scan_val;
unsigned int seed;
char post[2];

	scan_val = sscanf (seed_str, "%d%1s", &seed, post);			// return from scan stored in scan_val. Only valid if = 1

	if (scan_val == 1)
	{
	   check_int = 1;							// valid seed
	   srand(seed);
	}
	else
	{
	   check_int = 0;							// invalid seed, will ask for a new seed
	   printf("set_seed: invalid seed\n");
	}
    return check_int;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
//	STEP 1, 2, 3
   	*one   = (rand() % 8) + 1;			// random # from 1-8 stored in these addresses
	*two   = (rand() % 8) + 1;
	*three = (rand() % 8) + 1;
	*four  = (rand() % 8) + 1;
// 	STEP 4
	solution1 = *one;				// makes copies of all the values stored in solution#
	solution2 = *two;				// solution# can be used without declaring as a local variable
	solution3 = *three;				// seeing that it was declared as a global variable above.
	solution4 = *four;
 	guess_number = 1;

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
	int perfect = 0;
	int misplaced = 0;
	char post[2];
	int scan_val;
	int return_val;
	int w, x, y, z;
	int w_paired = 0, x_paired = 0, y_paired = 0, z_paired = 0;
	int soln1_paired = 0, soln2_paired = 0, soln3_paired = 0, soln4_paired = 0;
	
	scan_val = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);

// checks input validity 
	if ((scan_val == 4) && ((w>0)&&(w<9)) && ((x>0)&&(x<9)) && ((y>0)&&(y<9)) && ((z>0)&&(z<9)))
	{		
		return_val = 1;		// input is valid and can proceed
		*one = w;		// stores guesses into addresses
                *two = x;
                *three = y;
                *four = z;

/* 1. Check the guess number against the corresponding solution number to find perfect matches (correct number in the correct location). Do this for all fou
 * r numbers. Count the number of perfect matches. If there is a perfect match, mark the guess and solution as "paired" (possibly using another variable)
 * . If the first guess number is not paired yet, check it against the second solution number (if it is also not paired). If it matches, count a misplaced m
 * atch and mark the second solution number as paired.  If the second number did not match, repeat Step 2 for the third solution number. If the third soluti
 * on number does not match, try the fourth. Repeat 2-3 for the second guess number (if it is not already paired), then the third guess number, then the fou
 * rth.
*/
//	STEP 1				   Checks for perfecr values first. If perfect value found, marks soln and guess as paired (1)	
	if (solution1 == w)
	{
		perfect = perfect + 1;
		w_paired = 1;
		soln1_paired = 1;
	}
	if (solution2 == x)
	{
		perfect = perfect + 1;
		x_paired = 1;
		soln2_paired = 1;
	}
	if (solution3 == y)
	{
		perfect = perfect + 1;
		y_paired =1;
		soln3_paired = 1;
	}
	if (solution4 == z)
	{	
		perfect = perfect + 1;
		z_paired = 1;
		soln4_paired = 1;
	}
// 	STEP 2, 3 FOR INTEGER W -- Only cares if values have not yet been paired, and same concept applies to all following loops
	if (!w_paired)
	{
	  if((!soln2_paired)&&(w == solution2))
	    {
	      misplaced = misplaced + 1;
	      soln2_paired = 1;
	    }
	   else if((!soln3_paired)&&(w == solution3))
	    {
	      misplaced = misplaced + 1;
	      soln3_paired = 1;
	    }
	    else if((!soln4_paired)&&(w == solution4))
	    {
	      misplaced = misplaced + 1;
	      soln4_paired = 1;
	    }
	}
//	STEP 2, 3 FOR INTEGER X
	if (!x_paired)
	{
	  if((!soln1_paired)&&(x == solution1))
	    {
	      misplaced = misplaced + 1;
	      soln1_paired = 1;
	    }
	   else if((!soln3_paired)&&(x == solution3))
	    {
	      misplaced = misplaced + 1;
	      soln3_paired = 1;
	    }
	    else if((!soln4_paired)&&(x == solution4))
	    {
	      misplaced = misplaced + 1;
	      soln4_paired = 1;
	    }
	}	
//	STEP 2, 3 FOR INTEGER Y
	if (!y_paired)
	{
	  if((!soln1_paired)&&(y == solution1))
	    {
	      misplaced = misplaced + 1;
	      soln1_paired = 1;
	    }
	  else if((!soln2_paired)&&(y == solution2))
	    {
	      misplaced = misplaced + 1;
	      soln2_paired = 1;
	    }
	   else if((!soln4_paired)&&(y == solution4))
	    {
	      misplaced = misplaced + 1;
	      soln4_paired = 1;
	    }
	}
//	STEP 2, 3 FOR INTEGER Y
	if (!z_paired)
	{
	  if((!soln1_paired)&&(z == solution1))
	    {
	      misplaced = misplaced + 1;
	      soln1_paired = 1;
	    }
	  else if((!soln2_paired)&&(z == solution2))
	    {
	      misplaced = misplaced + 1;
	      soln2_paired = 1;
	    }
	   else if((!soln3_paired)&&(z == solution3))
	    {
	      misplaced = misplaced + 1;
	      soln3_paired = 1;
	    }
// STEP 4 COMPLETED
	 }
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
	guess_number = guess_number + 1;
	}
	else							// NO VALID GUESS. ASKS FOR NEW GUESS
	{
		printf("make_guess: invalid guess\n");
		return_val = 0;
	}
    return return_val;
}
