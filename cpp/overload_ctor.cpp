#include <iostream>
using namespace std;

enum ea{
	a0 =0,
	a1,
};

enum eb{
	b0 =0,
	b1=10
};
enum ec{
	c0 =0,
	c1=100
};

struct abc{
	const ea a_;
	const eb b_;
	const ec c_;
	abc(ea a=a0,eb b=b0,ec c=c0):a_(a),b_(b),c_(c)
	{}
	abc(eb b=b0,ec c=c0):a_(a0),b_(b),c_(c)
	{}
	abc(ec c=c0):a_(a0),b_(b0),c_(c)
	{}
	int operator()()
	{
		return static_cast<int>(a_)+static_cast<int>(b_)+static_cast<int>(c_);
	}
};
int main() {
	// your code goes here
	cout<<abc(a1)()<<endl;
	cout<<abc(b1)()<<endl;
	cout<<abc(c1)()<<endl;
	cout<<abc(a1,b1)()<<endl;
	//out<<abc(a1,c1)()<<endl;
	//cout<<abc(b1,b1)()<<endl;
	cout<<abc(a1,b1,c1)()<<endl;
	return 0;
}