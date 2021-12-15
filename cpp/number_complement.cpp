#include <cmath>
//考虑2的倍数以及特别数1
class Solution {
public:
    int findComplement(int num) 
    {
        //checkNumOne(num);
        int i=0;
        for(; pow(2,i)<=num; ++i)
        {
           // std::cout<<i<<std::endl;
        }
        return checkNumOne(num)?0:(pow(2,i)-1-num);
    }
    bool checkNumOne(int num)
    {
        return num==1?1:0;
    }
};