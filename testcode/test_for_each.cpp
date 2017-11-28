#include <vector>
#include <algorithm>
#include <cstdio>


struct status{
	int s;
	status():s(7){}
	void set(const int s){this->s = s;}
};


template<int N>
struct fuck_status
{
	void operator()(status & r)
	{
		r.set(N);
	}
};


struct cprintf{
	void operator ()(const status & i)
	{
		printf("%d, ",i.s);
	}
};

#define MAX 11

status a[MAX];

template<int N>
struct fuck_status_with_vectorindex 
{
	void operator()(const int i)
	{
		a[i].set(N);
	}
};

int main()
{
	std::for_each(a,a+sizeof(a)/sizeof(status),cprintf());
	printf("\n");
	std::for_each(a,a+sizeof(a)/sizeof(status),fuck_status<5>());
	std::for_each(a,a+sizeof(a)/sizeof(status),cprintf());
	printf("\n");
	int tmp[] ={1.2,5,6,9};
	std::vector<int> v(tmp,tmp+sizeof(tmp)/sizeof (int));
	std::for_each(v.begin(),v.end(),fuck_status_with_vectorindex<3>());
	std::for_each(a,a+sizeof(a)/sizeof(status),cprintf());
	printf("\n");
	
}