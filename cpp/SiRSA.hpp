#if !defined __LEETCODE__SiRSA__
#define 	 __LEETCODE__SiRSA__
#include <vector>
using  std::vector;
//主要思路就是二分法，先去掉反序的部分，如果在反序中就反复迭代出来，否在就在剩余的有序序列中
class Solution
{
public:
	int search(const vector<int> &nums,int target )
	{
		vector<int>::const_iterator first=nums.begin(),last=nums.end();

		while(first!=last)
		{
			vector<int>::const_iterator mid = first +(last - first) /2;
			if (*mid==target) return std::distance(nums.begin(),mid);
			if (*first<=*mid)//前半段升序
			{
				if ((*first<=target) && (target<=*mid))
				{
					last=mid;
				}
				else
				{
					first = mid+1;
				}
			}
			else//后半段升序
			{
				if ((*mid<=target) && (target<=*(last-1)))
				{
					first = mid+1;
				}
				else
				{
					last=mid;
				}
			}
		}
		return -1;
	}
};


#endif //! __LEETCODE__SiRSA__