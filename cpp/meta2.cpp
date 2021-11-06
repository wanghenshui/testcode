
#include <iostream>

template <int L,int R>
struct meta_int_min
{
	static int const value =(L<R)?L:R;
};

int main()
{
	std::cout<<meta_int_min<50,4>::value<<std::endl;
	static int const i=50,j=4;
	std::cout<<meta_int_min<i,j>::value<<std::endl;
}