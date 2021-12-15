#ifndef __LEETCODE__VALID_PARENTHESES__
#define __LEETCODE__VALID_PARENTHESES__
#include <stack>
#include <string>
using std::string;
using std::stack;
class Solution {
public:
    bool isValid(string const& s) 
    {
        string l = "([{";
        string r = ")]}";
        
        stack<char> stk;
        
        for(auto c:s)
        {
            if(l.find(c)!=string::npos)            
                stk.push(c);
            else
            {
                if(stk.empty() || stk.top()!=l[r.find(c)])
                    return false;
                else 
                    stk.pop();
            }
        }
        return stk.empty();
    }
};

#endif