#include <iostream>
using namespace std;

class InputNum
{
	int _num;
public:
	InputNum();
	~InputNum();
	int GetValue () const;	
};

InputNum::InputNum()
{
	cout << "Enter number : ";
	cin >> _num;
}

InputNum::~InputNum(){};

int InputNum::GetValue() const
{
	return _num;
}

int main(){
	InputNum num;
	cout << "The Value is  "<< num.GetValue() << "  \n";
}