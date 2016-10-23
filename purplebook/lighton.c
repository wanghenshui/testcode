/*
 * 开灯问题 
 * 有n盏灯，第一个人打开所有的灯
 * 第二个人按2的倍数灯开关
 * 第三个人按3的倍数灯开关
 * 共k个人 问哪些灯开的。
 * k<=n<=1000
 * 输入n k
 *
 * 这个提供了一个取余的好思路，可用在三位数成比例那个问题
*/

#include <stdio.h>
#include <string.h>
#define max 1024
int array[max];


int main()
{
	memset(array,0,sizeof(array));
	int n,k,i,j;
	scanf("%d %d",&n,&k);

	//这个循环是为了将所有状态保存起来。
	for(i=1; i<=k; i++)
		for(j=1; j<=n; j++)
			if(j%i == 0) array[j] = !array[j];

	
	//这个循环是输出所有非0的位
	for(i=1; i<=n;i++)
		if(array[i]) printf("%d ",i);

	printf("\n");
	return 0;
}

