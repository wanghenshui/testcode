#include <iostream>

using namespace std;
typedef struct test
{
	int info;
}test;
test array[20];
int main()
{
	for (int i=0;i<20;i++)
	{
		array[i]=i;
		//cout<<array[i]<<endl;
		cout<<array[i].info<<endl;
	}
}