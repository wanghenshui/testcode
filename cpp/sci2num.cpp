#include <iostream>
#include <sstream>
#include <string>
using namespace std;



template <typename T>
T sci2num(const string & str)
{
	stringstream ss(str);
	T tmp;
	ss >> tmp;
	if(ss.fail())
		throw("wtf " + str);

	return tmp;
}


int main()
{
	try{
		cout << sci2num<double>("1.234e5")<< endl;
		cout << sci2num<int>("1")<< endl;
		cout << sci2num<int>("p")<< endl;
	}catch(const string &e)
	{
		cerr<<e<<endl;
	}


}
