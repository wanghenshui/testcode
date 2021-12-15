#ifndef __LEETCODE__S2D__
#define __LEETCODE__S2D__
#include <vector>

using std::vector;
class Solution
{
public:
	 bool searchMatrix(const std::vector<std::vector<int> > v,int target)
	 {
	 	if (v.empty()) return false;

	 	const size_t m = v.size();
	 	const size_t n = v.front().size();

	 	int first =0, last = m*n;

	 	while(first!=last)
	 	{
	 		int mid = first +(last -first)/2;
	 		int value = v[mid/n][mid%n];

	 		if (value == target) 
	 			return true;
	 		else if(value <target)
	 			first = mid +1;
	 		else
	 			last = mid;
	 	}
	 	return false;
	 }	
};

#endif //! __LLETCODE__S2D__