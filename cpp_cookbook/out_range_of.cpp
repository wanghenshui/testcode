#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

struct out_range_of
{
	out_range_of(int min, int max):min_(min),max_(max){}
	bool operator()(int x)
	{
		return (x<min_) ||(x>max_);
	}
	int min_;
	int max_;
};

int main()
{
	std::vector<int> v ={6,12,14,24,32};
	remove_copy_if( v.begin(),
					v.end(),
					ostream_iterator<int>(cout, " "),
					out_range_of(10,25));
}