#include <stdio.h>

#define PEVAL(cmd) printf(#cmd ": %g\n",cmd)

int main()
{
	double *plist = (double []){1,2,3};
	double list[] = {1,2,3};
	PEVAL(sizeof(plist)/(sizeof(double)+0.0));

	PEVAL(sizeof(list)/(sizeof(double)+0.0));
}
