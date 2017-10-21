#ifndef __PRODUCT__HPP__
#define __PRODUCT__HPP__
#include <iostream>
using std::cout;
using std::endl;
class product
{
public:
	virtual ~product() = 0;
protected:
	product(){}
};
product::~product()
{}

class concrete_product : public product
{
public:
		concrete_product()
		{
			cout << "concrete product ... "<<endl;
		}
		~concrete_product()
		{}
};
#endif
