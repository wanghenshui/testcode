/*
 * 水仙花数 
 * ABC = A^3 + B^3 + C^3
 *
*/
#include <stdio.h>
#include <math.h>

int main()
{
	int i = 100;
	for (i=100; i<1000; i++)
		{
			int A = i/100 %10;
			int B = i/10  %10;
			int C = i%10;
			if (i == pow(A,3)+pow(B,3)+pow(C,3))
				printf ("%d\n",i);
		}
	return 0;
}
