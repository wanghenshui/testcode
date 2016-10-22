/*
*进制转换 输入数（n）和进制b 输出b进制数
*思路应该是字符串
*/

#include <stdio.h>
int main()
{
	int b,n;
	scanf("%d %d",&n,&b);
	printf("%*",b,n);
	return 0;

}