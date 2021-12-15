#ifndef __LEETCODE__Search_for_a_Range_STL__
#define __LEETCODE__Search_for_a_Range_STL__
#include <algorithm>
#include <vector>
using std::vector;
using std::distance;
class Solution
{
public:
    vector<int> searchRange(vector<int> & nums,int target)
    {
	const int l = distance(nums.begin(),lower_bound(nums.begin(),nums.end(),target));
	const int u = distance(nums.begin(),prev(upper_bound(nums.begin(),nums.end(),target)));

	if((nums.size()==0) //reference binding to null pointer of type 'value_type'
		||(nums[l] != target))
		return vector<int> {-1,-1};
	else
		return vector<int> {l,u};
    }
};


#endif //! __LEETCODE__Search_for_a_Range_STL__
