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
	{
		for(j=2; j<i; j++) //这里改成j<= sqrt(double(i));更佳，因为是对称的
		{
			if(i%j != 0) 
				continue;
			//如果没除开就继续除
			else 
				loca[i] = !loca[i];
				break;
			//除开了，说明不是质数是素数，记录下来，反着打印就可以了
		}
		//大圈继续算,这个continue加不加都可以。
		continue;

	}


	for(i=2; i<101; i++)
		if(!loca[i]) printf("%d ",i);

	printf("\n");

	return 0;
}
