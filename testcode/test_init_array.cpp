struct A
{
	int a[10];
	A():a({1}){};
};

#include <iostream>
using namespace std;

int main(){
	A t;
	for(int i=1;i<10;i++)
	{
		cout<< t.a[i]<<'\t';
	}
	cout<<'\n';
}
