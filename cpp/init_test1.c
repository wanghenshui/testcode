#include <stdio.h>
int main()
{

	int x;
	printf("x=[%d], bool x==(1&&x)=[%d]\n",x,(x == (1 && x)));
  	return x == (1 && x);
}