class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        vector <int> nums3;
        nums3.resize(nums1.size()+nums2.size()); 
        merge(nums1.begin(),nums1.end(),nums2.begin(),nums2.end(),nums3.begin());
        sort(nums3.begin(),nums3.end());
        if (nums3.size()%2)
        {
            return nums3[nums3.size()/2];
        }
        else
        {
            return (nums3[nums3.size()/2-1]+nums3[nums3.size()/2])/2.0;
        }
    }
};