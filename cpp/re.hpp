class Solution {
public:
    int removeElement(vector<int>& nums, int val) 
    {
     auto last = remove(nums.begin(),nums.end(),val)   ;
     return distance(nums.begin(),last);
    }
};