#include <vector>
#include <iostream>
#include <algorithm>
using std::reverse;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
/*
题目描述

数组的 左旋操作 是指在对于一个长度为 n 的数组 把所有的元素都向左移动 一个 单元。
举个栗子 : 如果对数组[1, 2, 3, 4, 5]进行两个单位的左旋 最终结果等于[3, 4, 5, 1, 2]。

	现在给出一个长度为 n 的数组 以及向左旋转的单位数 d
	需要输出旋转后的数组 用一行空格符分隔的数字序列表示
	输入格式

	标准输入

	第一行给出两个整数用空格分隔表示 n 和 d
	接下来一行 n 个用空格分隔的整数表示原始数组 a
	限制条件

	1 <= n <= 100000
	1 <= d <= n
	1 <= a[i] <= 1000000
	输出格式

	标准输出

	输出一行长度为 n 用空格分隔的整数序列 表示 a 数组向左旋转 d 个单元以后的结果
	样例输入

	5 4
	1 2 3 4 5
	样例输出

	5 1 2 3 4
	*/

int main()
{
	int n;
	int d;
	cin >> n >> d;
	vector<int> res(n, 0);
	for (int i = 0; i < n; i++) { cin >> res[i]; }

	reverse(res.begin(), res.begin() + d);
	reverse(res.begin() + d, res.end());
	reverse(res.begin(), res.end());

	for (auto&v : res)	cout << v << " ";
	cout << endl;

	//system("pause");
	return 0;
}
