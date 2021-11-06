#ifndef __ABSTRACT_PRODUCT_HPP
#define __ABSTRACT_PRODUCT_HPP
#include <iostream>
using std::cout;
using std::endl;
class AbstractProductA
{
public:
	virtual ~AbstractProductA();
protected:
	AbstractProductA();
};

AbstractProductA::AbstractProductA(){}
AbstractProductA::~AbstractProductA(){}


class AbstractProductB
{
public:
	virtual ~AbstractProductB();
protected:
	AbstractProductB();
};

AbstractProductB::AbstractProductB(){}
AbstractProductB::~AbstractProductB(){}

class pa1: public AbstractProductA
{
public:
	pa1()
	{
		cout<<"pa1"<<endl;
	}
	~pa1(){}
};


class pa2: public AbstractProductA
{
public:
	pa2()
	{
		cout<<"pa2"<<endl;
	}
	~pa2(){}
};


class pb1: public AbstractProductB
{
public:
	pb1()
	{
		cout<<"pb1"<<endl;
	}
	~pb1(){}
};


class pb2: public AbstractProductB
{
public:
	pb2()
	{
		cout<<"pb2"<<endl;
	}
	~pb2(){}
};
#endif
