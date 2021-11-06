#include <stdio.h>
int main()
{
	int a,b,c,sum;
	printf("input three numbers. split with space\n");
	scanf("%d %d %d",&a,&b,&c);
	sum = (a+b+c)*2 +7;
	printf("%d is what you got", sum);
	return 0;
}