#ifndef __LEETCODE__ATOI__
#define __LEETCODE__ATOI__

#include <limits.h>

class Solution {
public:
    int myAtoi(string str) 
    {
        long res=0;
        int flag=1;
        
        for(int i=0;i!=str.size();)
        {
            i = str.find_first_not_of(' ');
            if(str[i] == '-' || str[i] == '+' )
                flag =(str[i++]) == '-'? -1:1;
            
            while('0'<=str[i]&&str[i]<='9')
            {
                res = res*10 +(str[i++]-'0');
            }

            if(res*flag>=INT_MAX)
            	return INT_MAX;
            if(res*flag<=INT_MIN)
            	return INT_MIN;
        }
        return  res*flag;
    }
};

#endif //! __LEETCODE__ATOI__