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

	//��ȫȡ����2 5 0 �ĸ���

	long long trailingZeros(long long n) {
		//ע��auto��������
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