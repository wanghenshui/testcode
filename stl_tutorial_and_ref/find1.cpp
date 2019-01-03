#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	list<int> coll;
	for (int i = 20; i < 40; ++i)
	{
		coll.push_back(i);
	}

	auto pos25 = find(coll.begin(), coll.end(),25);
	auto pos35 = find(coll.begin(), coll.end(),35);
	cout<<"max "<<*max_element(pos25,++pos35);
	cout<<"min "<<*min_element(pos25,++pos35);
}