#include <cstdio>

struct test{
	static void f(){printf("static %s \n",__FUNCTION__);}
	int m;
};

int main()
{
	test::f();
	test * t= new test();
	t->f();	
}