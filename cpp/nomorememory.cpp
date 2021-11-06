#include <iostream> 
#include <new>
#include <cstdlib>
void nomorememory()
{
	std::cerr<<"unableto satisfy request for memory"<<std::endl;
	std::abort();
}

int main()
{
	std::set_new_handler(nomorememory);
	int * pbigdataarray = new int[100000000000];
}

