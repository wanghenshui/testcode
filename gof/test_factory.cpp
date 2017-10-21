#include <iostream>
using std::cout;
using std::endl;

#include "factory.hpp"

int main()
{
	factory* fac = new concrete_factory();
	product* p= fac->create_product();
	return 0;
}

