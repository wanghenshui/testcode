#include <iostream>
#include <cstdio>
int main()
{
	int i = 67;
	float f = * (float *)(&i);
	std::cout << f << std::endl;
	printf("%f",f);
}
