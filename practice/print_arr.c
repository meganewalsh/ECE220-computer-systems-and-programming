#include <stdio.h>
void print_arr(int, int *, int);

int main()
{
int bound = 0, cntr, return_val = 0;
int arr[100];

	do
	{
	//printf("How many elements would you like in the array? (<=100)\n");
	return_val = scanf("%d\n", &bound);
	}
	while ( return_val != 1 || bound <= 0 || bound > 100);

	for(cntr = 0; cntr < bound; cntr++)
	{
		printf("Element %d:\n", (cntr+1));
		scanf("%d", &arr[cntr]);
	}
	printf("Your array is:  {");
	print_arr(bound, arr, 0);
	printf(" } \n");
return 0;
}

void print_arr(int bound_pa, int *arr_pa, int i_pa)
{
	if(i_pa < bound_pa)
	{
		printf(" %d", arr_pa[i_pa]);
		print_arr(bound_pa, arr_pa, (i_pa+1));
	}
}


