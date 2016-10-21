#include <iostream>

int main()
{
	int sum = 0,val = 0;
	while (val<10)
	{
		sum +=val;
		++val;
	}
	std::cout << "Sum" << sum << std::endl;
	return 0;
}
