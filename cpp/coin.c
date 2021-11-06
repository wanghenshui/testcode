//硬币问题，1,5,10,50,100,500 
//A元至少需要多少枚
//
//
#include <stdio.h>

const int V[6] = {1,5,10,50,100,500};

//input
int C[6];
int A;

int min(int a,int b)
{

	return a<b?a:b;
}

void solve()
{
	int ans = 0;
	for (int i=5; i>=0; i--)	
	{
		int t = min(A/V[i],C[i]);
		A -= t*V[i];
		ans += t;	
	}
	printf("%d\n",ans);
}

int main()
{
	scanf("%d,%d,%d,%d,%d,%d,%d",&C[0],&C[1],&C[2],&C[3],&C[4],&C[5],&A);
	solve();

	return 0;

}
