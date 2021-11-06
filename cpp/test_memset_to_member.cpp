#include <iostream>
#include <cstring> //for memset
class test_memset_to_member
{
	int a;
public:
	test_memset_to_member()
	{
		a = 0x99;	
	};
	~test_memset_to_member(){};
	void printprint()
	{
		std::cout<<std::hex<<&test_memset_to_member::print<< " is what you got\n";
	}
	void print()
	{
		std::cout <<std::hex<< a << " is what you got \n";
	}
};

test_memset_to_member test;
int main()
{
	test.print();
	test.printprint();
	memset(&test,7,sizeof test);
	test.print();
	test.printprint();
}