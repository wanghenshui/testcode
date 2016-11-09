//ox score
//OOXXOXXOOO 1 2 0 0 1 0 0 1 2 3 =10
#include <stdio.h>
#include <string.h>
typedef unsigned int uint;
const unsigned int MAX = 81;
char a[MAX];
uint sum = 0;

uint score(uint i,uint tmpsum)
{
	i+=1;
	tmpsum +=1;
	if(a[i]=='O')	score(i,tmpsum);
	if(a[i]=='X')	
		sum +=tmpsum;
		return 0;
}
int main()
{
	
	memset(a,'\0',sizeof(a));
	uint tmpsum=0;
	scanf("%s",a);
	//recrusion
	for(uint i=0;i<MAX;i++)
	{
		if(a[i]=='0')	continue;
		if(a[i]=='O')	score(i,tmpsum);
		if(a[i]=='X')	continue;
	}
	printf("%d\n",sum);
	return 0;
}
