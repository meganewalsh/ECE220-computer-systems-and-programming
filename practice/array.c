#include <stdio.h>

int main()
{
int one, two, three, four, five;
int numbers[5];
int cntr;

	printf("Please create an array with five elements..\n");

	printf("Element 1: ");
	scanf("%d", &one);
	numbers[0] = one;

	printf("Element 2: ");
	scanf("%d", &two);
	numbers[1] = two;

	printf("Element 3: ");
	scanf("%d", &three);
	numbers[2] = three;

	printf("Element 4: ");
	scanf("%d", &four);
	numbers[3] = four;

	printf("Element 5: ");
	scanf("%d", &five);
	numbers[4] = five;

	printf("Here is your array: [");
        for(cntr = 0; cntr <= 4; cntr++)
        	printf(" %d ", numbers[cntr]);
	printf("]\n");

return 0;
}

