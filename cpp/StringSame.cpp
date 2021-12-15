/*
题目描述

给定两个字符串，请编写程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。这里规定大小写为不同字符，且考虑字符串中的空格。

给定一个string stringA和一个string stringB，请返回一个bool，代表两串是否重新排列后可相同。保证两串的长度都小于等于5000。
测试样例：

"This is nowcoder","is This nowcoder"

返回：true

"Here you are","Are you here"

返回：false


*/
//思路，还是hash
//注意，两字符串长度不等是一个可以优化的点
class Same {
public:
    bool checkSam(string stringA, string stringB) {
        // write code here
		
		if(stringA.size()!=stringB.size())
			return false;
		
        int count[257]={0};
        for(auto v: stringA)
            count[v]++;
        for(auto v:stringB)
            count[v]--;
        
        for(auto v:count)
        {
            if(v!=0)
                return false;
        }
        return true;
    }    
};