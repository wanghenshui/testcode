#include <iostream>
#include <typeinfo>
template <typename T>
void print_typeof(const T & x)
{
	std::cout<<typeid(x).name()<<"\n";
}

int main()
{
	double x;
	print_typeof(x);
	int a;
	print_typeof(a);
	float c;
	print_typeof(c);
}
