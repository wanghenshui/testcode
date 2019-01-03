#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	list<int> coll1 = {1,2,3,4,5,6,7,8,9};
	for (auto e:coll1)
	{
		cout<<e<<' ';
	}
	cout<<endl;
	vector<int> coll2;
	coll2.resize(coll1.size());

	copy(coll1.cbegin(), coll1.cend(),coll2.begin());
	for (auto e:coll2)
	{
		cout<<e<<' ';
	}
	cout<<endl;
	deque<int> coll3(coll1.size());

	copy(coll1.cbegin(), coll1.cend(),coll3.begin());
	for (auto e:coll3)
	{
		cout<<e<<' ';
	}
	cout<<endl;
}	