#include <iostream>
using std::cout;
using std::endl;

#include "abstract_factory.hpp"


int main()
{
	abstract_factory * f1 = new concrete_factory1();
	f1->create_a();
	f1->create_b();

	abstract_factory * f2 = new concrete_factory2();
	f2->create_a();
	f2->create_b();
	return 0;
}
