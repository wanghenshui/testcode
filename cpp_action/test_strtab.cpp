#include <iostream> // for cout
#include "strtab.hpp"



int main()
{
	StringTable s;
	s.ForceAdd("One");
	s.ForceAdd("Two");
	s.ForceAdd("Three");


	int id = s.Find("One");
	std::cout<<id<< '\n';

	int id2 = s.Find("Three");
	std::cout<<id2<< '\n';

	int id3 = s.Find("Two");
	std::cout<<id3<< '\n';

	int id4 = s.Find("Fuck");
	std::cout<<id4<< '\n';	

	for (int i = 0; i < 3; ++i)
	{
		std::cout<<s.GetString(i)<<std::endl;
	}
}