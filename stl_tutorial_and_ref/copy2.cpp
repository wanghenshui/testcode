#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	list<int> coll1 = {1,2,3,4,5,6,7,8,9};

	vector<int> coll2;
	copy(coll1.cbegin(), coll1.cend(),back_inserter(coll2));
	for (auto e:coll2)
	{
		cout<<e<<' ';
	}
	cout<<endl;

	deque<int> coll3;
	copy(coll1.cbegin(), coll1.cend(),front_inserter(coll3));
	for (auto e:coll3)
	{
		cout<<e<<' ';
	}
	cout<<endl;

	set<int> coll4;
	copy(coll1.cbegin(), coll1.cend(),inserter(coll4,coll4.begin()));
	for (auto e:coll4)
	{
		cout<<e<<' ';
	}
	cout<<endl;
}	