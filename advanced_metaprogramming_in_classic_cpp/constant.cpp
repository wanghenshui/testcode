#define M_HELPER(NAME,VALUE)			\
static T NAME()					\
{						\
	static const T NAME##_ = (VALUE);	\
	return NAME##_;				\
}

template<typename T>
struct constant
{
	M_HELPER(PI,3.14159265358);
};

#include <iostream>
using namespace std;
int main()
{
	cout<< constant<double>::PI()<<'\n';
	cout<< constant<int>::PI()<<'\n';
}
