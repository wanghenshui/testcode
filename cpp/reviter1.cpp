#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	std::vector<int> coll;
	for (int i = 1; i < 10; ++i)
	{
		coll.push_back(i);
	}
	copy(coll.crbegin(), coll.crend(),ostream_iterator<int>(cout," "));
	cout<<endl;
	return 0;
}