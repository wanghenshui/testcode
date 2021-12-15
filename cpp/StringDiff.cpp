/*
题目描述

请实现一个算法，确定一个字符串的所有字符是否全都不同。这里我们要求不允许使用额外的存储结构。

给定一个string iniString，请返回一个bool值,True代表所有字符全都不同，False代表存在相同的字符。保证字符串中的字符为ASCII字符。字符串的长度小于等于3000。
测试样例：

"aeiou"

返回：True

"BarackObama"

返回：False


*/

//解题思路 
//排序去重
//hash 数组去重
//注意字符256个，这是一个可以优化的点
//正则过滤 这个不容易想到

class Different {
public:
	bool checkDifferent(string iniString) {
		// write code here
		const int SIZE = iniString.size();
		if (SIZE > 256)
			return false;
		sort(iniString.begin(), iniString.end());
		iniString.erase(unique(iniString.begin(), iniString.end()), iniString.end());

		return SIZE == iniString.size();
	}
};