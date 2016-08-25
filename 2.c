#include <stdio.h>
#include <stdlib.h>

int main()
{
	short i,n;
	i=0;
	n=0;
	
	printf("show me what you got");
	scanf("%d",&n);
	for(i=0;i<n;++i)
	{
		if(i%6==0)
			printf("\n");
		printf("%12d",rand());
	}
	printf("\n");
	return 0;

}