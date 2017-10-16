#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

inline ios_base& floatnormal(ios_base& io)
{
	io.setf(0, ios_base::floatfield);//what's wrong?
	return io;
}


int main()
{
	ios_base::fmtflags f=cout.flags();
	double pi = 3.141592653;
	cout<<"pi :" <<scientific<<pi *1000<<endl;
	cout<<"pi :" <<floatnormal<<pi<<endl;
	cout.flags(f);
}
