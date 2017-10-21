#ifndef __SINGLETON__HPP
#define __SINGLETON__HPP

#include <iostream>
using std::cout;
using std::endl;

class singleton
{
	static singleton* instance_;
public:
	static singleton* get();
protected:
	singleton()
	{
		cout<< "singleton ... "<< endl;
	}
};

singleton* singleton::instance_ = nullptr;

singleton* singleton::get()
{
	if(instance_ == nullptr)
		instance_ = new singleton();

	return instance_;
}

#endif
