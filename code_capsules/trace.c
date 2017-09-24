#include <stdio.h>

#define trace(x,format)\
printf(#x " = %"#format "\n",x)


int main()
{
	int i=1;
	float x=2.0;
	char* s="three";


	trace(i,d);
	trace(x,f);
	trace(s,s);
}