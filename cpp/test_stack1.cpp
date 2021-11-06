#include "cppa.hpp"
#include "stack.h"
int main()
{
	cppa::stack stk;
	stk.push(1);
	stk.push(2);
	stk.push(3);

	for(cppa::stack_seq seq(stk); !seq.at_end(); seq.advance())
		cout<<"	"<< seq.getnum();
	cout<<endl;
}