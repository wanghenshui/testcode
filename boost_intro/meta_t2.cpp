#include <type_traits>
#include <boost/mpl/if.hpp>
template <typename T>
struct meta_type_pointer :
	boost::mpl::if_<std::is_pointer<T>,
		typename std::add_const<
			typename std::remove_pointer<T>::type
			>::type,
		typename std::add_pointer<
			typename std::add_const<T>::type
			>::type
>{};

#include <iostream>
int main()
{
	if(std::is_same<meta_type_pointer<int>::type,const int *>::value)
		std::cout<<"fuck it"<<std::endl;
	if(std::is_same<meta_type_pointer<int *>::type,const int>::value)
		std::cout<<"fuck it T**"<<std::endl;
}