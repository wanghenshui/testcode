#include <iostream> 

void swap(int &x,int &y)
{
	x = x+y;
	y = x-y;
	x = x-y;
}

int main()
{
	int i=1,j=2;
	swap(i,j);
	std::cout<<"i="<<i<<std::endl;
	std::cout<<"j="<<j<<std::endl;
}