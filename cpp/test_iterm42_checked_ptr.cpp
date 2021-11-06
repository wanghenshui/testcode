#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class checked_ptr{
public:
	explicit checked_ptr(T*p):p_(p){cout<<"p created at "<< p_ << endl;}
	~checked_ptr()
	{
		delete p_;
		cout<<"p deleted "<<p_<<endl;
	}
	T * operator -> (){return get();}
	T & operator * () {return *get();}
private:
	T* p_;
	T* get() const{return p_;}
	checked_ptr(const checked_ptr&);
	checked_ptr & operator =(const checked_ptr&);
};

struct ab
{
	int a;
	int b;
};
int main()
{
	checked_ptr<ab> p (new ab());
}
