#include "prototype.hpp"


int main(){
	prototype * p = new concrete_prototype();
	prototype * p2 = p->clone();
	cout<< p <<endl;
	cout << p2 <<endl;
	delete p;
	delete p2;
	return 0;
}
