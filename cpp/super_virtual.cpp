#include <iostream>
using namespace std;

struct base{
	virtual void foo()
	{
		cout<<"base::foo"<<endl;
	}
};

struct derived : public base{
	virtual void foo()
	{
		cout<<"derived::foo"<<endl;
	}
};

int main()
{
	derived *p = new derived();

	p->foo();
	p->base::foo();
}
