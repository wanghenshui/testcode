#include <iostream>
#include <sstream>
#include <string>

using namespace std;

double sci2double(const string& str)
{
	stringstream ss(str);
	double d = 0;
	ss >> d;

	if(ss.fail())
	{
		string s = "unable to format ";
		s+=str;
		s=+"as a number";
		throw(s);
	}

	return d;
}


int main()
{
	try{
		cout << sci2double("1.234e5")<< endl;
		cout << sci2double("6.02e-2")<< endl;
		cout << sci2double("asdf")<< endl;
	}
	catch(string& e)
	{
		cerr << "whoops "<< e << endl;
	}
}
