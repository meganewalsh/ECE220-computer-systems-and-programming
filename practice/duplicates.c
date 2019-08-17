#include <stdio.h>

int main()
{
int num_elements, index, val, index2;
int duplicates = 0;
int numbers[num_elements];

	printf("Insert the number of elements to be stored in the array: ");
	scanf("%d", &num_elements);
	
	printf("Please insert %d elements for your array: \n", num_elements);
	
	for(index = 0; index < num_elements; index++)
	{
		printf("Element %d: ", (index+1));
		scanf("%d", &val);
		numbers[(index)] = val;
		for(index2=(index-1); index2 >= 0; index2--)
		{
			if(val == numbers[index2])
				duplicates++;
				break;
		}
	}

	printf("Here is your array: [");
	for(index = 0; index < num_elements; index++)
		printf(" %d ", numbers[index]);
	printf("]\n");
	
	printf("Total number of duplicates found in the array is: %d \n", duplicates);

return 0;	
}
