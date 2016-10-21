#include <iostream>

int main()
{
	int sum = 0;
	for(int i=-10; i<=10; ++i)
	{
		sum += i;
		std::cout <<"Sum  "<< sum <<" and i is "<< i <<std::endl;
	}
	std::cout << sum << std::endl;
	return 0;
}
