#include <iostream>

class A{};
class B{

	void print(){std::cout <<"B\n";}
};
B b;

int main()
{
	std::cout<<sizeof(A)<<std::endl;
	std::cout<<sizeof(b)<<std::endl;
}