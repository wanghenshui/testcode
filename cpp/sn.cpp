class Solution {
public:
    int singleNumber(vector<int>& nums) {
    
    // vector<value_t>::iterator it = find_if(nums.begin(), nums.end(), single);  
    //return *it;    
    int ret =0;
    for (int i = 0; i <nums.size(); i++)
    {
        ret ^= nums[i];
    }
    return ret;
    }
};