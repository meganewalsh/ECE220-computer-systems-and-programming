#include <stdio.h>

int main()
{
int temp, years, weeks, days, input;

printf("Insert a number of days: ");
scanf("%d", &input);

years = input / 365;
temp = input % 365;
weeks = temp / 7;
days = temp % 7;

printf("%d days equals %d years, %d weeks, and %d days\n", input, years, weeks, days);
return 0;
}

