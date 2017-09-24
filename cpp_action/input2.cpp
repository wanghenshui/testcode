#include "cppa.hpp"

class input2
{
	typedef int value_type ;
	value_type _num;
public:
	
	input2();
	~input2();
	value_type getValue() const;
	void addInput();
};
input2::input2()
{
	cout << "Enter number ";
	cin >> _num;
}
input2::~input2(){};

input2::value_type input2::getValue() const
{
	return _num;
}
 void input2::addInput()
 {
 	input2 anum;
 	_num = _num + anum.getValue();
 }

 int main()
 {
 	input2 num;
 	cout << "the value is "<< num.getValue() << "  \n";
 	num.addInput();
 	cout << "now the value is " << num.getValue() << "   \n";
 }