#include <stdio.h>
int find_largest(int *, int, int);

int main()
{
int arr[100], result;
int num_elem = 5;
arr[0] = 0;
arr[1] = 4;
arr[2] = 3;
arr[3] = 2;
arr[4] = 1;

	result = find_largest(arr, 0, num_elem);
	printf("The largest element in the array is: %d.\n", result);

return 0;
}

int find_largest(int *arr, int i, int num_elem)
{
int result = 0;

	if(arr[i+1] > arr[i] && (i+1) <= num_elem)
	{
		result = arr[i + 1];
		result = result + find_largest(arr, i++, num_elem);
		return result;
	}
	else if (arr[i+1] <= arr[i] && (i+1) <= num_elem)
	{
		result = 0;
		result = result + find_largest(arr, i++, num_elem);
		return result;
	}

return 0;
}

