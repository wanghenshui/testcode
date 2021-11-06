#include <iostream>
#include <algorithm>
#include "tracer.hpp"
using namespace std;
int main()
{
	sort_tracer input[] = {7,3,5,6,4,2,0,1,9,8};
	
	for(int i=0; i<10; ++i)
	{
		cout<<input[i].val()<<" ";
	}
	cout<<"\n";

	long created_at_start = sort_tracer::creations();
	long max_live_at_start = sort_tracer::max_live();
	long assigned_at_start = sort_tracer::assignments();
	long compared_at_start = sort_tracer::comparisons();

	std::sort<>(&input[0],&input[9]+1);
	cout<< sort_tracer::creations()-created_at_start <<'\n';
	cout<< sort_tracer::max_live()-max_live_at_start <<'\n';
	cout<< sort_tracer::assignments()-assigned_at_start <<'\n';
	cout<< sort_tracer::comparisons()-compared_at_start <<'\n';
}
