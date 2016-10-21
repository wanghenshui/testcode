#include <stdio.h>
static int j;

void funi(void)
{
	static int i = 0;
	i++;
	printf("i=%d\n",i);
}

void funj(void)
{
	j = 0;
	j++;
	printf("j=%d\n",j);
}
int main()
{
	int k = 0;
	for(k=0; k<10; k++)
	{
		funi();
		funj();
		
	}
	
	return 0;
}
