/*逆序输出
 * 
 *
*/

#include <stdio.h>
#define maxn 100

int main()
{
	int array[maxn];
	int input,i=0;
	
	while(scanf("%d",&input)==1)
		array[i++] = input;

	for(int j=i-1; j>0; j--)
		printf("%d\n",array[j]);

	printf("%d\n",array[0]);
	return 0;	
}
