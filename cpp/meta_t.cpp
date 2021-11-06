template <typename T>
struct meta_type_pointer
//返回const T*
{
	typedef const T* type;
};

template <typename T>
struct meta_type_pointer<T*>//偏特化
{
	typedef const T type;
};

#include <iostream>
#include <type_traits> //is_same<>
int main()
{
	if(std::is_same<meta_type_pointer<int>::type,const int *>::value)
		std::cout<<"fuck it"<<std::endl;
	if(std::is_same<meta_type_pointer<int *>::type,const int>::value)
		std::cout<<"fuck it T*";
}