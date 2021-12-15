/*
题目描述

利用字符重复出现的次数，编写一个方法，实现基本的字符串压缩功能。比如，字符串“aabcccccaaa”经压缩会变成“a2b1c5a3”。若压缩后的字符串没有变短，则返回原先的字符串。

给定一个string iniString为待压缩的串(长度小于等于10000)，保证串内字符均由大小写英文字母组成，返回一个string，为所求的压缩后或未变化的串。
测试样例

"aabcccccaaa"

返回："a2b1c5a3"

"welcometonowcoderrrrr"

返回："welcometonowcoderrrrr"


*/
//注意点
// to_string c++11 以及实现
// 之前使用push_back,int 转char 直接加了'0' 卡在这里了
//res.append(to_string(count));
class Zipper {
public:
    string zipString(string iniString) {
        const int SIZE= iniString.size();
        string res;
        int count=0;
        for(int i=0;i<SIZE;++i)
        {
            res.push_back(iniString[i]);
            count++;
            while(i+1<SIZE&&iniString[i]==iniString[i+1])
            {
                i++;count++;
            }
            res.append(to_string(count));
            count=0;
        }
        
        if(SIZE<=res.size())
            return iniString;
        else
            return res;
    }
};
