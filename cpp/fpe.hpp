#ifndef __LEETCODE__FPE__
#define __LEETCODE__FPE__
#include<vector>
using std::vector;

class Solution {
public:
    int findPeakElement(const vector<int> &num) 
    {
        int first = 0;
        int last = num.size()-1;
        
        while(first != last)
        {
            int mid1 = (first+last)/2;
            int mid2 = mid1+1;
            if(num[mid1] < num[mid2])// 局部升序，那就搜索直到降序
                first = mid2;
            else
                last = mid1;//局部降序，向前找升序点
        }
        return first;
    }
};

#endif //! __LEETCODE__FPE__