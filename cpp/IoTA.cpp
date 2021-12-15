class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
    {
        set<int> tmp_set (nums1.begin(),nums1.end());
        vector<int> out;
        for(auto&i :nums2)
            if(tmp_set.erase(i))
                out.push_back(i);
        return out;
    }
};