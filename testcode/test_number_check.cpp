#include <cstdio>

#define CHECK_NUMBER(x,BOUND,ret) do \
{\
	if ((x) >= (BOUND))\
	{\
		printf("Func %s, Line = %d, %s = %d, Need Check.", __FUNCTION__, __LINE__,#x,(x)); \
		return ret; \
	}\
} while (0);
#define RETURN_VOID
#define CHECK_NUMBER_RETURN_VOID(x,BOUND) CHECK_NUMBER(x,BOUND,RETURN_VOID)
#define CHECK_NUMBER_RETURN_INVALID(x,BOUND) CHECK_NUMBER(x,BOUND,0xFF)
#define CHECK_NUMBER1(x) CHECK_NUMBER_RETURN_VOID(x,1)
#define CHECK_NUMBER1_RETURN(x) CHECK_NUMBER_RETURN_INVALID(x,1)

void f()
{
	int tmp =2;
	CHECK_NUMBER1(tmp);
}
int f1()
{
	int tmp1 =3;
	CHECK_NUMBER1_RETURN(tmp1-1);
}
int main()
{
	f();
	printf("%d",f1());
}