#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;
using boost::bad_lexical_cast;

template <typename __cast_T>
bool is_valid(const string& snum)
{
	bool res=true;
	try
	{
		__cast_T tmp = lexical_cast<__cast_T>(snum);
	}
	catch (bad_lexical_cast &e)
	{
		res = false;
	}

	return res;
}


void test(const string& s)
{
	if(is_valid<int>(s))
		cout<<s<<" is a valid int"<<endl;
	else
		cout<<s<<" is NOT a valid int"<<endl;

	if(is_valid<float>(s))
		cout<<s<<" is a valid float"<<endl;
	else
		cout<<s<<" is NOT a valid float"<<endl;

	if(is_valid<double>(s))
		cout<<s<<" is a valid double"<<endl;
	else
		cout<<s<<" is NOT a valid double"<<endl;

}

int main()
{
	test("12345");
	test("1.2345");
	test("-12345");
	test("- 12345");
	test("  12.345");
	test("asdf");
}