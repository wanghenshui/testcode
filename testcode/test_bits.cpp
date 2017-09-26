#include <iostream>
int main()
{
	std::cout<<sizeof(char)<<std::endl;
	std::cout<<sizeof(short)<<std::endl;
	std::cout<<sizeof(int)<<std::endl;
	std::cout<<sizeof(char *)<<std::endl;
	std::cout<<sizeof(long)<<std::endl;
	std::cout<<sizeof(long long)<<std::endl;
	struct test{
	char a;
	short b;
	int c;
	//long d;
	};
	std::cout<<sizeof(test)<<std::endl;
}
