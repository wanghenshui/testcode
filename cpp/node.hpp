#ifndef __node__
#define __node__ 1

#include <iostream> //: for cout and endl

class node
{
public:
	virtual	~node(){}
	virtual double calc () const = 0;
};

class NumNode :public node
{
	const double _num;
public:
	NumNode(double num)
	:_num(num){}
	double calc () const;
};

double NumNode::calc() const
{
	std::cout << "Numberic node " << _num << std::endl;
	return _num;
}

class BinNode : public node
{
public:
	BinNode(node * pl, node * pr)
	:_pl(pl),_pr(pr){}

	~BinNode();
protected:
	node * const _pl;
	node * const _pr;
};

BinNode::~BinNode()
{
	delete _pr;
	delete _pl;
}


class AddNode : public BinNode
{
public:
	AddNode(node * pl, node * pr)
	:BinNode(pl,pr){}
	double calc () const;
};

double AddNode::calc() const
{
	std::cout << "adding \n";
	return _pl->calc() + _pr->calc();
}

class MultNode:public BinNode
{
public:
	MultNode(node * pl, node * pr)
	: BinNode(pl,pr){}
	double calc() const;
	//~MultNode();	
};

double MultNode::calc() const
{
	std::cout << "Multing\n";
	return _pl->calc() * _pr->calc();
}
#endif//:define guard end