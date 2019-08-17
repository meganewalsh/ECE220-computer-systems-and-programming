#include <stdio.h>
#include <stdlib.h>
int main()
{
int rand_num, guess;

//Random number is between 1 and 10
srand((unsigned int)time(NULL));
rand_num = (rand() % 10) + 1;
printf("A random number has been generated. Good luck.\n");
	for(int GUESSctr = 1; GUESSctr <= 3; GUESSctr++)
 	{
 	   printf("Guess number %d\n", GUESSctr);
 	   printf("Enter your guess: ");
 	   scanf("%d", &guess); 	   

	   if(guess > rand_num)
 	   {
	      if(GUESSctr == 3)
	        printf("Your guess is incorrect, and you ran out of guesses. The correct answer is %d.\n", rand_num);
 	      else
		printf("Your guess is too high! Try again.\n");
 	   }
 	   else if(guess < rand_num)
 	   {	
	      if(GUESSctr == 3)
	   	printf("Your guess is incorrect, and you ran out of guesses. The correct answer is %d.\n", rand_num);
	      else
		printf("Your guess is too low! Try again.\n");
	   }
	   else
	   {
	      printf("Your guess is correct!\n");
 	      break;
 	   }
 	}
return 0;
}
