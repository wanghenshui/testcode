#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct _equal
{
	const int num;
	int index;
	_equal(const int n):num(n){
		cout<<"ctor"<<endl;
	}
	_equal(const _equal& n):num(n.num){
		
		cout<<"copy ctor"<<endl;
	}
	
	void operator()(int i)
	{
		if(i==num)
		{
			cout<<"found it"<<i<<endl;
			index = i;
		}
		
	}
	~_equal(){

		cout<<index<<"end it"<<endl;
	}
	
};
int main() 
{
	// your code goes here
	vector<int> v;
	for(int i=0;i<5;++i)
	{
		v.push_back(i);
	}
	
	for_each(v.begin(),v.end(),_equal(9));
	return 0;
}