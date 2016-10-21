#include <stdio.h>
#include <stdlib.h>

int main()
{
	short i,n;
	printf("show me what you got \n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		if(i%6==0)
			printf("\n");
		int tmp ;
		tmp= rand(n);
		printf("%12d",tmp);
	}
	printf("\n");
	return 0;

}