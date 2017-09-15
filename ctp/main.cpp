#include "tuple.hpp"

char a[]="1234";

int main()
{
	rm::tuple<int, int, int, char *> config_tuple;
	config_tuple = rm::make_tuple(1,2,3,a);
}

