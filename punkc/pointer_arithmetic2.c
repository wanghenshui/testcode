#include <stdio.h>

typedef char* string ;

int main()
{
	string list[] ={"f","s","t",NULL}	;

	for(string *p=list; *p != NULL; p++)
	{
		printf("%s\n",*p);
	}

	return 0;
}
