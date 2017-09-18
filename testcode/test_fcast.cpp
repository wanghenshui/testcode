#include <iostream>
#include <cstdio>
int main()
{
	int i = 67;
	float f = * (float *)(&i);
	std::cout << f << std::endl;
	printf("%f\n",f);

	double f2 =3.141592653;
	char c = *(char *)(& f2);
	std::cout <<c << std::endl;

	printf("%d\n",c);
}
