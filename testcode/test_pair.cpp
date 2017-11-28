#include <iostream>
#include <utility>
using namespace std;

void f1(int i)
{
	cout<<i<<endl;
}
void f2(int i)
{
	cout<<i*i<<endl;
}
typedef void (*fp)(int );

const std::pair<int,fp> func_array[]=
{
	std::make_pair(1,f1),
	std::make_pair(2,f2),
};


int main() {

	int a = 2;
	for(int i=0;i<2;++i)
	{
		if(a==func_array[i].first)	
			func_array[i].second(a);
	}
	
	return 0;
}