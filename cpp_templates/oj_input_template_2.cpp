#include <stdio.h>
int main() 
{
	int a,b;
	while(scanf("%d %d",&a, &b) != EOF) // 输入结束时，scanf函数返回值为EOF(-1)，即没有数据输入时会退出while循环
	{
		printf("%d\n",a+b);
	}
	return 0; 
}