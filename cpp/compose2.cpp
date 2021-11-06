#include <iostream>
#include <algorithm>
#include <functional>
#include <ext/functional>


int main() {
	// your code goes here
	int a[] = {1,2,6,8,9,5,4,1,22};
	int * p = std::find_if(a,a+sizeof(a)/sizeof(a[0]),
			 __gnu_cxx::compose2(std::logical_and<bool>(),
			std::bind2nd(std::greater<int>(),7),
			std::bind2nd(std::less<int>(),23))
			);
			std::cout<<*p<<std::endl;
	return 0;
}