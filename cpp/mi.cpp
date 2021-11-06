#include <iostream>
using namespace std;
struct Base1
{
	virtual ~Base1(){}
	void print(){cout<<"Base1"<<'\n' ;}
	int B1;
};
struct Base2
{
	virtual ~Base2(){}
	void print(){cout<<"Base2"<<'\n' ;}
	int B2;};
	
struct Base3
{
	virtual ~Base3(){}
	void print(){cout<<"Base3"<<'\n' ;}
	int B3;
};

struct Base4
{
	virtual ~Base4(){}
	void print(){cout<<"Base4"<<'\n' ;}
	int B4;
};


struct derived1 :public Base1
{
	virtual ~derived1(){}
	void print(){cout<<"derived1"<<'\n' ;}
	int D;
 };
	
struct derived2 :public Base1,public Base2
{
	virtual ~derived2(){}
	void print(){cout<<"derived2"<<'\n' ;}
	int D;
};
	
struct derived3 :public Base1,public Base2,public Base3
{
	virtual ~derived3(){}
	void print(){cout<<"derived3"<<'\n' ;}
	int D;
};

struct derived4 :public Base1,public Base2,public Base3,public Base4
{
	virtual ~derived4(){}
	void print(){cout<<"derived4 "<<'\n' ;}
	int D;
};


int main()
{
	Base1 b1;
	Base2 b2;
	Base3 b3;
	derived1 d1;
	derived2 d2;
	derived3 d3;
	derived4 d4;	
	
	cout<<sizeof (b1)<<'\n' 
		<<sizeof (b2)<<'\n'
		<<sizeof (b3)<<'\n'
		<<sizeof (d1)<<'\n'
		<<sizeof (d2)<<'\n'
		<<sizeof (d3)<<'\n'
		<<sizeof (d4)<<'\n'
		<<sizeof (int*)<<'\n'
		<<sizeof (int)<<'\n';
}

/*
root@WQW:/mnt/e/100k/testcode# ./a.out                          
12                                                              
12                                                              
12                                                              
16                                                              
28                                                              
40                                                              
52                                                              
8                                                               
4                                                               
root@WQW:/mnt/e/100k/testcode# g++ mi.cpp -g -fpack-struct=8    
root@WQW:/mnt/e/100k/testcode# ./a.out                          
16                                                              
16                                                              
16                                                              
16                                                              
32                                                              
48                                                              
64                                                              
8                                                               
4
*/                                                             