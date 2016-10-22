/*
*	调和级数，保留三位小数
*
*
*/

#include <stdio.h>
int main()
{
	int n=0;
	scanf("%d",&n);
	float sum =0;
	for(;n!=0;n--)
		sum += (float) 1/n;
	printf("%0.3f\n",sum);
	return 0;
}