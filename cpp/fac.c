#include <stdio.h>

unsigned int f(unsigned int n)
{
	return n==0?1:f(n-1)*n;
}

int main()
{
	
	unsigned int n = 0;
	scanf("%d",&n);
	unsigned int fac = f(n);
	printf("%d\n",fac);
	return 0;
	
}
