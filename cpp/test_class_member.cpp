struct math
{
	template <typename T>
	T sq(T x) const {return x*x;}
};

template <typename T>
struct _math{
	template <typename _T>
	static T product(T x, _T y){return x*y;}
};
#include <iostream>

int main()
{
	double A = math().sq(3.14);
	double B = _math<double>().product(3.14,5);
	std::cout<<A<<"||||"<<B<<std::endl;

}

