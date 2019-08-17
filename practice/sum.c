#include <stdio.h>
int main()
{
int range, final_sum;
	
	printf("Enter the last number of the range starting from 1: ");
	scanf("%d", &range);
	final_sum = find_sum(range);
	
	printf("The sum of the values in this range is: %d\n", final_sum);

	return 0;
}

int find_sum(int range)
{
int sum;
	if(range > 0)
	{
	  sum = range + find_sum(range - 1);
	  return sum;
	}
	else
	  return 0;
}
