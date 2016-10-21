#include <iostream>

class World
{
	public:
		World(){ std::cout<<"hello!\n";}
		~World(){ std::cout<<"Fuck off\n";}
};




int main()
{
	World smallWorld;
	std::cout<<"hello from the other side\n";
}
