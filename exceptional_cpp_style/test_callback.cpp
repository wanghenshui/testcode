#include <iostream>
using namespace std;

class callbackbase
{
public:
	virtual void operator()() const{}
	virtual ~callbackbase(){}
};

template<typename T>
class callback:public callbackbase
{
public:
	typedef void(T::*F)();
	callback(T& t,F f):t_(&t),f_(f){}
	void operator()()const
	{
		(t_->*f_)();
	}
private:
	T* t_;
	F f_;
};

template<typename T>
callback<T> make_callback(T& t,void(T::*f)())
{
	return callback<T>(t,f);
}

struct A{
	void f()
	{
		cout<<"A.f()"<<endl;
	}
};
int main()
{
	A a;

	callback<A> c(&a,A::f());
	c();
	callback<A> d = make_callback(&a,A::f());
	d();
	return 0;
}


