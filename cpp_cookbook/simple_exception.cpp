#include <iostream>
#include <string>
using namespace std;

class Exception{
public:
	Exception(const string & msg) : msg_(msg){}
	~Exception(){}
	string get_msg(){
		return msg_;
	}
	// try to overload << sometime
private:
	string msg_;
};

void f()
{
	throw(Exception("sorry whattttt?"));
}

int main()
{
	try{
		f();
	}
	catch(Exception& e )
	{
		cout << "what exception?"<< e.get_msg() <<endl;
//		cout << "what exception?"<< e <<endl;
	}
}
