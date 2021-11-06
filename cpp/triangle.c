/*
 * 输出n层倒三角形
 *
 * n<21
 *
 * 思路 当前行i，从0开始，每行逐个j轮训
 * 每行2n-1-i 个字符，其中前i个字符是空格。所以剩下的全打#
*/

#include <stdio.h>
#define error 1
int main()
{
	int n = 0;
	int i,j;

	scanf("%d",&n);
	if (20 < n)
		return error;
	for(i=0;i != n;i++)
	{
		for(j=0; j!=i; j++)
			printf(" ");
		for(j=0; j!= 2*(n-i)-1;j++)
			printf("#");
		printf("\n");
	}
	return 0;
}
