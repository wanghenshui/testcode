/*UVa1583
 *x+x/100+x/10%10 +x%10 = y
 *  min x?
 *程序有问题
 */
#include <stdio.h>
#include <string.h>
#define MAXN 10005
int ans[MAXN];

int main()
{
	int t,n;
	memset(ans,0,sizeof(ans));
	for(int i=1; i<MAXN; i++)
	{
		int x=i, y=i;
		while(x>0)
		{
			y+=x%10;
			x/=10;
		}

		if(ans[y]==0||i<ans[y])
			ans[y]=i;
	}

	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}

	return 0;
	
}

