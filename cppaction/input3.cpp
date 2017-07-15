#include "cppa.hpp"
// warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]

class input3
{
	int _num;
public:
	input3(char msg[]);
	~input3();
	int getValue() const;
	void addInput(char msg[]);
};

input3::input3(char msg[])
{
	cout <<msg;
	cin >> _num;
}
input3::~input3(){};
int input3::getValue() const
{
	return _num;
}

void input3::addInput(char msg[]){
	input3 tmp(msg);
	_num = getValue() + tmp.getValue();
}

const char ss[] = "the sum is ";
int main()
{
	input3 num("enter a number   ");
	num.addInput("add one");
	num.addInput("and add more");
	cout << ss << num.getValue() << " \n";
}	