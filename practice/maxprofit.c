#include <stdio.h>

int main()
{
int prices[5] = {1, 2, 3, 4, 5};
int temp, i, small, large, temp2, n = 5;

   large = prices[0];
   for(i = 1; i < n; i++)
   {
      if(prices[i] > large)
      { 
	 large = prices[i];
	 temp = i;
      }
   }
   
   small = large;
   for(i = (temp-1); i >= 0; i--)
   {
      if(prices[i] < small)
      {
         small = prices[i];
         temp2 = i;
      }
   }
printf("%d\n", (temp2-temp));
printf("%d\n", (large-small));

if(temp2-temp == 0)
   return 0;
else
   return (large-small);
}
