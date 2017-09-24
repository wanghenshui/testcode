#include "node.hpp"

int main()
{
	//(20.0 + -10.0 ) * 0.1
	node * p1 = new NumNode(20.0);
	node * p2 = new NumNode(-10.0);
	node * p3 = new AddNode(p1,p2);
	node * p4 = new NumNode(0.1);
	node * p5 = new MultNode(p3,p4);
	double x = p5->calc();
	std::cout << x<<std::endl;
	delete p5;
}