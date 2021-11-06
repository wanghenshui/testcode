#include <cstdio>
int main()
{
	int a=32;
	unsigned char c= static_cast<unsigned char>(a);
	printf("a=%d\n",c );
	char b=33;
	c= static_cast<unsigned char>(b);
	printf("b=%d\n",c );
	unsigned char d=9;
	c= static_cast<unsigned char>(d);
	printf("d=%d\n",c );
	return 0;
}