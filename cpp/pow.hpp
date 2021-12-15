#ifndef __LEETCODE__POW__
#define __LEETCODE__POW__
//TODO:  with binary search
class Solution {
public:
    double myPow(double x, int n) 
    {
        if(n<0)
        {
            x=1/x;
            n=-n;
        }
        //if i return with myPow(1/x,-n);
        //can not pass that case. i dont know why
        //1.00000
        //-2147483648
        
        unsigned long long lln= n;   
        double res=1;
        while(lln)
        {
            if(lln&1)
                res*=x;
            x*=x;
            lln>>=1;
        }
        return res;
    }
};
#endif //! __LEETCODE__POW__