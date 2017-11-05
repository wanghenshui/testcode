#include <iostream>
#include <vector>
using namespace std;
int n, target;
int a[5];

bool dfs(int i, int sum)
{
	if (n==i)
	{	
		cout<< i<<'\t'<<sum<<'\n';
		return sum == target;
	}
	if (dfs(i+1, sum)) 
	{

		cout<< i<<'\t'<<sum<<'\n';
		return true;
	}
	if (dfs(i+1, sum+a[i])){

		cout<< i<<'\t'<<sum<<'\n';
		return true;
	}
	return false;
}

void solve()
{
	if(dfs(0,0))
		cout<<"find it\n";
	else
		cout<<"fuck it\n";
}
int main()
{
	cout<<"array of num :";
	cin>> n;

	cout<<"array :";
	for(int i=0; i<n; ++i)
	{
		cin>>a[i];
		cout<< i<<'\t'<<a[i]<<'\n';
	}
	cout<<"target :";
	cin>>target;

	solve();
}
