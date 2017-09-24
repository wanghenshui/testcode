#include <iostream>

class Matter
{
	const int _identifimer;
public:
	Matter(int id);
	~Matter();
};

Matter::Matter(int id):_identifimer(id){
	std::cout << "Matter for " << _identifimer << " created\n";
}
Matter::~Matter(){
	std::cout << "Matter of "<< _identifimer << " destroyed\n";
}

class world5
{
	const int _identifimer;
	const Matter _matter;
public:
	world5(int id) ;
	~world5();
};
world5::world5(int id) :_identifimer(id),_matter(_identifimer){
	std::cout <<"Hello form world5 "<<_identifimer << "\n";
}
world5::~world5(){
	std::cout << "Goodbye from world5 "<< _identifimer <<" \n";
}

world5 TheUniverse(1);

int main()
{
	world5 smallWorld(2);
	return 0;
}