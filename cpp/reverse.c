/*逆序输出
 * 
 *
*/

#include <stdio.h>
#define maxn 10000
//数组比较大要定义在main函数外面
int array[maxn];

int main()
{
	int input,i=0;
	
	while(scanf("%d",&input)==1)
		array[i++] = input;

	for(int j=i-1; j>0; j--)
		printf("%d\n",array[j]);

	printf("%d\n",array[0]);
	return 0;	
}
