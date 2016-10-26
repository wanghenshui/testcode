/*
 * prime 质数
 *  输出1~100之间的质数。第四章第二题
 *  这个问题等同于点灯问题
 */
#include <stdio.h>
#include <string.h>
int main()
{
	int i,j;
	int loca[120];
	memset(loca,0,sizeof(loca));
	
	for(i=2; i<=100; i++)
		for(j=2; j<i; j++)
			if(i%j==0) loca[i] = !loca[i];
	

	for(i=2; i<101; i++)
		if(loca[i]) printf("%d ",i);

	printf("\n");

	return 0;
}
