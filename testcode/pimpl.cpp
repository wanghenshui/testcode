#include <iostream>
#include <string>
class Test{
	class TestIMPL;//declar
	TestIMPL *p;
public:
	Test();
	~Test();
	void print();
};

class Test::TestIMPL
{
	size_t data;
	std::string name;
public:
	void print();
};

Test::Test()
{
	p = new TestIMPL();
}

Test::~Test()
{
	delete p;
}

void Test::print()
{
	p->print();
}

void Test::TestIMPL::print()
{
	std::cout<<"'sup bitch!,here is  " << __FUNCTION__<<"\n";
}


int main()
{
	Test t;
	t.print();
}
