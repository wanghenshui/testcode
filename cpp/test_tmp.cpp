namespace w{
template<class T> inline
T sum(T *f, T *l)
{
	T sum;
	for(sum=0; f!=l; ++f)
		sum +=*f;
	return sum;
}
} //:end of w



#include <iostream>
#include <vector>
int main()
{
	std::vector<float> v = {1.1,2.2,3.3,4.4};
	std::vector<int> v2 = {1,1,1,1,1,1,1};
	auto s1 = w::sum(&v[0],&v[3]);
	auto s2 = w::sum(&v2[0],&v2[4]);
	std::cout << s1 << " "<< s2<<std::endl;
}