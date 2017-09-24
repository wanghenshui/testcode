#include <stdio.h>

int a[4] = {0,1,2,3};
int index = 0;

int & current()
{
	return a[index];
}

int main()
{
	current() = 10;
	index = 3;
	current() = 20;

	for(int i=0; i<4; ++i)
		printf("%d\n",a[i]);
	putchar('\n');
}