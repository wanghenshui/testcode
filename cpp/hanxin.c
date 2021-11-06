/*
 * 韩信点兵问题
 * 三人一排，五人一排，七人一排，排尾人数a,b,c
 * 总人数10~100之间。
 * 样例输入 
 * 2 1 6
 * 2 1 3
 * 输出
 * 41
 * no answer
 *
*/
#include <stdio.h>

int main()
{
	int a,b,c;
	scanf("%d %d %d",&a,&b,&c);
	if ((a>3)||(b>5)||(c>7))
	{
		printf("input error\n");
		return 1;
	}
	int tmp=0;
	for(tmp = 10; tmp <= 100; tmp++)
	{
		if(tmp%3==a&&tmp%5==b&&tmp%7==c)
		{
			printf("%d\n",tmp);
			return 0;
		}
		if (tmp == 100)
		{
			printf("no answer\n");
			return 1;
		}
	}
}
