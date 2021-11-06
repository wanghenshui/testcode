#include <stdio.h>

void set_elmt(int*a, int const *b)
{
	a[0] = 3;
}

int main()
{
	int a[10] = {};

	int const *b = a;
	
	set_elmt(a,b);

	printf("a[0]=[%d],b[0]=[%d]",a[0],b[0]);
}
