#include <stdio.h>
#include <stdlib.h>

extern "C"{
int myentry(int argc, char *argv[])
{
	    printf("myentry\n");
	    exit(0);
}
}
