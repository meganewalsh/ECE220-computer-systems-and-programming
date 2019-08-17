#include <stdio.h>
#include <stdlib.h>

// After the user enters a row index (under 50) that they desire, this program uses a loop
// and a factorial function to calculate and print the values in that row of Pascal's
// Triangle.

double factorial(int);
int main()
{
  int row_index;
  int k;
  double num, denom1, denom2;
  long ans;

  printf("Enter the row index : ");
  scanf("%d",&row_index);

  // Your code starts from here
  for (k=0 ; k <= row_index; k++)
  {
	num = factorial(row_index);
	denom1 = factorial(k);
	denom2 = factorial(row_index - k);
	ans = (long)((num / (denom1*denom2))+ 0.5);	// Adding 0.5 allows rounding to whole number
	printf("%ld ", ans);
  }
  printf("\n");
  return 0;
}



double factorial(int x)					// Use a double as number is very large
{
  double answer = 1;
  int y;
	for (y = 1; y <= x; y++) 
	{
	answer = y * answer;
	}
  return answer;					// Return value back to main
}
