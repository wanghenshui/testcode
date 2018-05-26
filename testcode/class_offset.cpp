#include <iostream>
struct base1{
	virtual ~base1(){}
	int val1;
	};
struct base2{
	virtual ~base2(){}
	int val2;};
struct derived :public base1,base2{
	virtual ~derived(){}
	int val3;};

using namespace std;
int main()
{
	base1 b1;
	base2 b2;
	derived d1;
	
	cout<<"base1 val1 offset "<<&base1::val1<<'\n';
	cout<<"base2 val2 offset "<<&base2::val2<<'\n';
	cout<<"derived val1 offset "<<&derived::val1<<'\n';
	cout<<"derived val2 offset "<<&derived::val2<<'\n';
	cout<<"derived val3 offset "<<&derived::val3<<'\n';
	
	cout<<&b1<<'\n' <<&b1.val1<<'\n'<<&b2<<'\n'<<&b2.val2<<'\n';
	cout<<&d1<<'\n' <<&d1.val1<<'\n'<<&d1.val2<<'\n'<<&d1.val3<<'\n';
	
	
	cout<<sizeof (b1)<<'\n' <<sizeof (b2)<<'\n'<<sizeof (d1)<<'\n'<<sizeof (int*)<<'\n'<<sizeof (int)<<'\n';
}
