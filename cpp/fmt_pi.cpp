#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	ios_base::fmtflags f = cout.flags();

	double pi = 3.14159265;

	cout <<"pi :"<<setprecision(5)<<pi<<endl;
	cout <<"pi :"
		 <<fixed
		 <<showpos
		 <<setprecision(3)<<pi<<endl;

	cout <<"pi :"
		 <<scientific
		 <<noshowpos
		 <<pi*1000<<endl;
	cout.flags(f);
}
