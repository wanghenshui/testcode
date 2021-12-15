
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int ones = 0, sum = 0;
        const int len = nums.size();
        for (int i = 0; i < 32; ++i) {
            ones = 0;
            for (int val: nums)
                ones += val >> i & 1;
            sum += (len - ones) * ones;
        }
        return sum;
    }
};
/*
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) 
    {
        uint32_t sum=0;
        for(int i=0;i<nums.size();i++)
        {
            for(int j=i+1; j!=i&&j<nums.size();j++)
            {
                sum += hammingDistance(nums[i],nums[j]);
            }
        }
        return sum;
    }
    
    int hammingDistance(int l,int r)//(int x, int y) 
    {
//	    if((x^y)==0) return 0;
//	    return (x^y)%2 + hammingDistance(x/2,y/2);
        int k = l ^ r, res = 0;
        while(k) {
            res += k & 1;
            k >>= 1;
        }
        return res;
    }
};
*/