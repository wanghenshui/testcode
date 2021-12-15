#pragma once
namespace trailing_zeros 
{
class Solution
{
public:
	/*
	* @param n: A long integer
	* @return: An integer, denote the number of trailing zeros in n!
	*/

	//完全取决于2 5 0 的个数

	long long trailingZeros(long long n) {
		//注意auto会有问题
		long long n0 = 0;
		while (n)
		{
			n0 += n / 5;
			n /= 5;
		}
		return n0;

		return n0;
	}
};
}