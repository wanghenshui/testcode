#include <iostream>
#include <vector>
using namespace std;

std::vector<int> f(int a=1, int b=0)
{
	cout<<a<<"	"<<b<<endl;
	std::vector<int> v;
	v.push_back(a);
	v.push_back(b);
	return v;
}

int main()
{
	std::vector<int> v1=f();
	std::vector<int> v2=f(2);
	std::vector<int> v3=f(3,4);

	cout<<v1[0]<<"	"<<v1[1]<<endl;
	cout<<v2[0]<<"	"<<v2[1]<<endl;
	cout<<v3[0]<<"	"<<v3[1]<<endl;
}