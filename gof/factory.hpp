#ifndef __FACTORY__HPP
#define __FACTORY__HPP
#include <iostream>
using std::cout;
using std::endl;

#include "product.hpp"
class product;

class factory
{
public: 
	virtual ~factory()=0;
	virtual product* create_product()=0;
protected:
	factory();
};

factory::factory(){}
factory::~factory(){}

class concrete_factory : public factory
{
public:
	~concrete_factory();
	concrete_factory();

	product* create_product();
};

concrete_factory::concrete_factory()
{
	cout<<"concrete factory ..."<<endl;
}
concrete_factory::~concrete_factory(){}

product* concrete_factory::create_product()
{
	return new concrete_product();
}





#endif
