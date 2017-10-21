#ifndef __PROTOTYPE__HPP
#define __PROTOTYPE__HPP
#include <iostream>
using std::cout;
using std::endl;

class prototype{
public:
	virtual ~prototype(){}
	virtual prototype* clone() const = 0;
protected:
	prototype(){}
};

class concrete_prototype :public prototype
{
public:
	concrete_prototype()
	{
		cout<<" conncrete prototype empty"<<endl;
	}
	~concrete_prototype(){
		cout<<"~destory prototype "<<endl;
	}
	concrete_prototype(const concrete_prototype& c)
	{
		cout<<" concrete prototype copy ..."<<endl;
	}
	prototype* clone() const
	{
		return new concrete_prototype(*this);
	}
};

#endif
