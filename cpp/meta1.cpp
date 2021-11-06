#include <iostream>
//#include <boost/config.hpp>
template <int N, int M>
struct meta_add_func
{
	//same way
	//BOOST_STATIC_CONSTANT(int, value = N+M);
	//enum {value = N+M};
	static int const value = N+M;
};
int main()
{
	std::cout<<meta_add_func<10,11>::value <<std::endl;
}