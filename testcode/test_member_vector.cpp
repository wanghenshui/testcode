#include <vector>
using namespace std;
#include <iostream>
struct A
{
	vector<int> a_;
};
int main()
{
	A * pa=new A();
	cout<<	sizeof(pa)<<'\n';
	for(int i=0;i<100;++i)
	{
		pa->a_.push_back(i);
		cout<<pa->a_[i]<< ' ';
	}
	cout<< '\n';

	A a;
	cout<<	sizeof(a)<<'\n';
	for(int i=0;i<100;++i)
	{
		a.a_.push_back(i);
		cout<<a.a_[i]<< ' ';
	}
	cout<< '\n';
	cout<<	sizeof(a)<<'\n';
	cout<<a.a_.capacity()<<'\n';
}
