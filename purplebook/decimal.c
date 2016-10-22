/*
 * 分数化小数
 * 输入a b c 分数a/b 化为小数，保留c位
 * a,b <10^6 c<=100
 * 输入多组数据
 * 问题，如何转化输入c为小数点位数
 * .*f
*/


#include <stdio.h>

int main()
{
	int a,b,c;
	while(scanf("%d %d %d",&a,&b,&c)&&(a||b||c))	
	{
		float sum = (float)	 a/b;
		
		printf("%.*f\n",c,sum);
	}


}
