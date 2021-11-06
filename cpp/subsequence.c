/* 子序列的和
 * 输入两个正整数 n<m<10^6
 * 输出Σ1/n^2+....1/m^2
 * 保留五位小数输入多组，输入0 0结束
 *
 * 注意问题
 * 1 强制类型转换 注意是(float) 1/(表达式), 不是(float) (1/表达式)，为了明确一点干脆写在后面好了
 * 2 保留小数点五位
 * 3 多组输入
 */
#include <stdio.h>
#include <math.h>
int main()
{
	int n,m;
	float sum=0;

	while(scanf("%d %d",&n,&m)&&(n||m))
		//这个是借鉴 while(scanf("%d",&a)==EOF)类似得来的
	{
		for (;n<m+1;n++)
		{
			sum += (float) 1/(pow(n,2));// 1/(float)pow(n,2)
		}
		printf("%0.5f\n",sum);
	}
	return 0;
}
