#ifndef __CPPA__STACK
#define __CPPA__STACK
namespace cppa{
const int maxStack = 4;

class stack
{
	typedef int value_type;
	value_type m_arr[maxStack];
	value_type m_top;
	friend class stack_seq;
public:
	stack();
	~stack();
	void push(value_type i);
	value_type pop();
	void print();
};

class stack_seq
{
	stack const& _stack;
	int current_index;
public:
	stack_seq(stack const & stack);
	~stack_seq();

	bool at_end() const;
	void advance();
	int getnum() const;
};
}		//: end of namespace cppa
#endif //:__CPPA__STACK END