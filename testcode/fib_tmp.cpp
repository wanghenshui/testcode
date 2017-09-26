template <int N>
struct fib
{
	static const long long res= fib<N-1>::res + fib<N-2>::res	;
};

template<>
struct fib<1>
{
	static const long long res=1	;
};
template<>
struct fib<0>
{
	static const long long 	res=1	;
};


#include <iostream>
using namespace std;

int main()
{
	cout<<fib<91>::res<<endl;
	
}