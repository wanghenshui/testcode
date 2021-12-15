class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        vector<int> bits(32,0);
        int i, j;
        for (i = 0; i < nums.size(); i++)
            for (j = 0; j < 32; j++)
                bits[j] += ((nums[i] >> j) & 1);
        // 如果某位上的结果不能被整除，则肯定目标数字在这一位上为
        int result = 0;
        for (j = 0; j < 32; j++)
            if (bits[j] % 3 != 0)
                result += (1 << j);
        return result;
    }
};