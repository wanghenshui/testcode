#include <iostream>
using namespace std;

void f(int *a)
{
	for(int i=0;i<8;++i)
	{
		if(a[i]==255)
			continue;
		cout<< a[i]<<'\n';
	}
}

int main()
{
	int a[]={1,255,2,255,3,4,5,256};
	f(a);
	return 0;
}
