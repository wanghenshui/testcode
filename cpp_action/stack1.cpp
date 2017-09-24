#include "cppa.hpp"
#include "stack.h"

namespace cppa{

stack::stack() :m_top(0){};
stack::~stack(){};

stack::value_type stack::pop()
{
	assert (m_top >0);
	--m_top;
	return m_arr[m_top];
}	

void stack::push(stack::value_type i)
{
	assert (m_top < maxStack);
	m_arr[m_top] = i;
	++m_top;
}
void stack::print()
{
	for(int i=0; i!= maxStack; ++i)
		cout<<m_arr[i]<<"   ";
	cout<<endl;
}

//----------------------------------------------------------------------//

stack_seq::stack_seq(stack const & stack) :current_index(0),_stack(stack){};
stack_seq::~stack_seq(){};
bool stack_seq::at_end() const
{
	return current_index == _stack.m_top;
}

void stack_seq::advance()
{
	assert(!at_end());
	++current_index;
}


int stack_seq::getnum() const
{
	assert(!at_end());//const成员函数不能调用非const成员函数 所以at_end得是const
//	 error: passing ‘const ’ as ‘this’ argument discards qualifiers [-fpermissive]
	return _stack.m_arr[current_index];
}

//----------------------------------------------------------------------//
}//: end of namespace cppa

/*
int main()
{
	cppa::stack stk;
	stk.push(1);
	stk.print();
	stk.push(2);
	stk.print();
	cout << stk.pop()<<"\n";
	stk.print();
	cout << stk.pop()<< "\n" ;
	stk.print();
}
*/