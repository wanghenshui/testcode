#include <map>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
typedef std::map<std::string, int> MyMap;

const MyMap::value_type rawData[] = {
   MyMap::value_type("hello", 42),
   MyMap::value_type("world", 88),
};

MyMap m(rawData, rawData + sizeof rawData / sizeof rawData[0]);

int main()
{
	MyMap::iterator it= m.find("hello");

	if(it == m.end())
		cout<<"what??"<<endl;
	else
		cout<<it->second<<endl;	
}