#ifndef __LEETCODE__LCS__
#define __LEETCODE__LCS__
#include <vector>
#include <unordered_map>
#include <algorithm>
using std::unordered_map;
using std::vector;
using std::max;
//Your algorithm should run in O(n) complexity.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

    	unordered_map<int,bool> used;

    	for(auto i:nums)	used[i]=false;

    	int longest=0;

    	for (auto i:nums)
    	{
    		if(used[i]) continue;
    		int length = 1;
    		used[i]=true;
    		//向两边扩展
    		for(int j=i+1;used.find(j)!=used.end();j++)
    		{
    			used[j]=true;
    			length++;
    		}

    		for (int j=i-1; used.find(j)!=used.end(); j--)
    		{
    			used[j]=true;
    			length++;
    		}
    		longest = max(longest,length);
    	}
    	return longest;        
    }
};
#endif //!LEETCODE__LCS__