#ifndef __LEETCODE__SIP__
#define __LEETCODE__SIP__
// aka redefine the lower_bound

#include <vector>
using std::vector;
#include <algorithm>
using std::distance;
using std::next;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) 
    {
    	return distance(nums.begin(),lower_bound(nums.begin(),nums.end(),target));
    }

    template <typename FIT,typename T>
    FIT lower_bound(FIT first,FIT last,T value) 
    {
    	while(first!=last)
    	{
    		auto mid = next(first,distance(first,last)/2);

    		if(value>*mid)
    			first =++mid;
    		else 
    			last = mid;
    	}
    	return first;
    }
};
#endif //! __LEETCODE__SIP__