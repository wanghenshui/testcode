#include <iostream>

void c()
{
	std::cout<<"c"<<'\n';
}

void d()
{
	std::cout<<"d"<<'\n';
}
struct RAII
{
	RAII()
	{
		c();
	}
	~RAII()
	{
		d();
	}
};
void e()
{
	std::cout<<"e"<<'\n';
	RAII a;
	//a;
}
int main()
{
	e();
	return 0;
}