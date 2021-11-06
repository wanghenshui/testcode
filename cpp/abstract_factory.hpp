#ifndef __ABSTRACT__FACTORY__HPP
#define __ABSTRACT__FACTORY__HPP
#include <iostream>
using std::cout;
using std::endl;
#include "abstract_product.hpp"
class AbstractProductA;
class AbstractProductB;

class abstract_factory
{
public:
	virtual ~abstract_factory();
	virtual AbstractProductA* create_a()=0;
	virtual AbstractProductB* create_b()=0;
protected:
	abstract_factory();
};

abstract_factory::abstract_factory(){}
abstract_factory::~abstract_factory(){}

class concrete_factory1:public abstract_factory
{
public:
	concrete_factory1(){}
	~concrete_factory1(){}
	AbstractProductA* create_a()
	{
		return new pa1();
	}
	AbstractProductB* create_b()
	{
		return new pb1();
	}
};


class concrete_factory2:public abstract_factory
{
public:
	concrete_factory2(){}
	~concrete_factory2(){}
	AbstractProductA* create_a()
	{
		return new pa2();
	}
	AbstractProductB* create_b()
	{
		return new pb2();
	}
};
#endif
