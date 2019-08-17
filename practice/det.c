#include <stdio.h>
int main()
{
int matrix[3][3];
int det;

//This program prints the determinant of a 3x3 matrix
	printf(" Here is the matrix format:\n");
	printf("  A  B  C\n");
	printf("  D  E  F\n");
	printf("  G  H  I\n");
	printf("Please input desired values in alphabetical order (i.e. A B C D E F G H I)\n");
	
//Displays matrix
int cntr;
	for(cntr = 0; cntr < 3; cntr++)
	{
		scanf("%d", &matrix[0][cntr]);
		printf(" %d", matrix[0][cntr]);
	}
	printf("\n");
	
	for(cntr = 0; cntr < 3; cntr++)
	{
		scanf("%d", &matrix[1][cntr]);
		printf(" %d", matrix[1][cntr]);
	}
	printf("\n");
	
	for(cntr = 0; cntr < 3; cntr++)
	{
		scanf("%d", &matrix[2][cntr]);
		printf(" %d", matrix[2][cntr]);
	}
	printf("\n");
printf(" That is the matrix that you entered.\n");
//Finds & prints determinant
	det = (matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[2][1]*matrix[1][2])) - (matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])) + (matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]));
	printf(" The determinant of that matrix is %d.\n", det);

return 0;
}

