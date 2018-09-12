#include <iostream>
#include <set>
#include <list>
using namespace std;

bool is_prime(int n)
{
	bool result = false;
	if (n > 1)
	{
		int k = ::sqrt(n);
		int i = 2;
		for (; i <= k; i++)
			if (n%i == 0) break;
		if (i > k)
			return true;
	}
	return result;
}


list<uint64_t> get_all_prime_divisors(uint64_t n)
{
	/*
	 * For example:
	 * get_all_prime_divisors(45) returns {5, 3} as a list.
	 * HINT-1: The order matters, make sure it's sorted from max to min.
	 * HINT-2: Don't include 1.
	 */
	std::set<uint64_t, greater<uint64_t> > s;
	int i = 2;
	while (n >= 2)
	{
		if (n%i == 0)
		{
			s.insert(i);
			n /= i;
		}
		else i++;
	}
	list<uint64_t> res(begin(s), end(s));
	return res;
}