#include <iostream>
#include <string>
using namespace std;

string get_file_ext(const string & s)
{
	size_t i = s.rfind('.',s.length());
	if(i != string::npos)
	{
		return(s.substr(i+1,s.length()-1));
	}
	return "";
}

int main(int argc, char**argv)
{
	string path = argv[1];
	cout<<get_file_ext(path)<<'\n';
}