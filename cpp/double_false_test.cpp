#include <iostream>
int global = -9;

int main()
{
	int tmp = !!global;
	std::cout <<"global="<<global<<std::endl;
	std::cout <<"!global="<<!global<<std::endl;
	std::cout << "!!global"<<!!global<<std::endl;
	std::cout <<"tmp="<<tmp<<std::endl;
	return 0;
}