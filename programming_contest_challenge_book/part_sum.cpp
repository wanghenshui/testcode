#include <iostream>
#include <vector>
using namespace std;
int n, target;
int a[65535];

bool dfs(int i, int sum)
{
	if (n==i)	return sum == target;
	if (dfs(i+i, sum)) return true;
	if (dfs(i+i, sum+a[i])) return true;
	return false;
}

int main()
{
	cout<<"array of num :";
	cin>> n;

	cout<<"array :";
	for(int i=0; i<n; ++i)
	{
		cin>>a[i];
	}
	cout<<"target :";
	cin>>target;

	if(dfs(0,0))
		cout<<"find it\n";
	else
		cout<<"fuck it\n";
}
