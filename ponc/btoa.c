//binary to ascii
//recrusion
#include <stdio.h>

void binary_to_ascii(unsigned int value)
{
	usigned int tmp = 0;
	tmp = value/10;
	if(tmp !=0)
		binary_to_ascii(tmp);
	putchar(value%10 + '0');
}

int main()
{
	unsigned int value = getchar();
	binary_to_ascii(value);
	return 0;
}