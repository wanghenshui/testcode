#ifndef __LEETCODE__SiRSAII__
#define __LEETCODE__SiRSAII__
#include <vector>
using std::vector;

//和33题不太一样，不是返回位置，只要找到就可以。（当然都找到了位置也很容易得到）
class Solution {
public:
    bool search(vector<int>& nums, int t) 
    {
        size_t f = 0,l=nums.size();

        while (f != l)
        {
        	const size_t m = f + (l-f)/2;
        	if (nums[m]==t)
        		return true;
        	if (nums[f]<nums[m])
        	{
        		if(nums[f]<=t && t<nums[m])//注意边界
        			l=m;
        		else
        			f=m+1;
        	}
        	else if(nums[f]>nums[m])
        	{
        		if(nums[m]<t && t<=nums[l-1])//注意边界
        			f=m+1;
        		else
        			l=m;
        	}
        	else
        		f++;//说明f是重复的
        }
        return false;
    }
};



#endif //!__LEETCODE__SiRSAII__