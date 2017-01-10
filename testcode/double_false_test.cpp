#include <iostream>
int global = 8;

int main()
{
	int tmp = !!global;
	std::cout <<"global="<<global<<std::endl;
	std::cout <<"!global="<<!global<<std::endl;
	std::cout << "!!global"<<!!global<<std::endl;
	std::cout <<"tmp="<<tmp<<std::endl;
	return 0;
}