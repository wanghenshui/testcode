class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        vector<int> index;
        for(vector<int>::iterator i=nums.begin(); i!=nums.end(); i++)
        {
            for(vector<int>::iterator j=i+1;j!=nums.end();j++)    
            {
                if(*i+*j == target)
                {
                    index.push_back(std::distance(nums.begin(),i));
                    index.push_back(std::distance(nums.begin(),j));
                    return index;
                }
            }
        }
    }
};