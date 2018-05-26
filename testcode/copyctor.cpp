#include <iostream>
using namespace std;
struct A{
	int a_;
	A(int a) :a_(a){}
	A(A other)
	{
		a_ = other.a_;
	}
	A(const A & other)
	{
		a_ = other.a_;
	}
	void print()
	{
		cout<<a_<<endl;
	}
};

int main()
{
	A a1(1);
	a1.print();
	A a2(a1);
	a2.print();	
}