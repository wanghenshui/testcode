#include <iostream>
using namespace std;

struct base{
	virtual ~base(){exit();}
	virtual void init(){cout<<"base init"<<endl;}
	virtual void exit(){cout<<"base exit"<<endl;}
	void	dispatch(){init();}
};

struct D:public base
{
	virtual void init(){cout<<"d init"<<endl;}
	void exit(){cout<<"d exit"<<endl;}
};

int main()
{
	D d;
	d.dispatch();
	base * p = new D();
	p->dispatch();
	delete p;
}
