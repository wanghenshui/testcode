#include <stdio.h>

int main()
{
	int evens[5] = {0,2,4,6,8};
	printf("the first even number is %i\n",*evens);


	int *positive_evens =&evens[1];
	printf("the first positive even number is %ii\n",positive_evens[0]);

	return 0;

}
