#include <iostream>
int main()
{
	int i=1;
	std::cout << "\x20" <<i++<<"\t"<<i++<<"\v"<<i++<<"\r"<<i++<<std::endl;
	return 0;
}