#include <iostream>
int global = 8;

int main()
{
	std::cout <<"global="<<global<<std::endl;
	std::cout <<"!global="<<!global<<std::endl;
	std::cout << "!!global"<<!!global<<std::endl;
	return 0;
}