#include <iostream>

class World
{
	public:
		World(int i)
		{
			std::cout << "hello from"<< i << ".\n";
		}
		~World()
		{
			std::cout<<"Fuck Off\n";

		}
};

World TheWorld(1);

int main()
{
	World smallWorld(2);
	std::cout<<"hello from main\n";
}
