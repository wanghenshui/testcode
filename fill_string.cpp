//: read an entire file into a single string
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in ("fill_string.cpp");
	string s,line;
	while(getline(in, line))
		s += line + "\n";
	cout << s;
}
///:~