#include <math.h> //erf sqrt
#include <stdio.h>

int main()
{
	printf("the integral of a Normal(0,1) disrtibution\n ");
	printf("between +-1.96 is : %g\n",erf(1.96*sqrt(1/2.)));
}
