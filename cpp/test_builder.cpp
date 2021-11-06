#include "builder.hpp"
#include "director.hpp"

int main()
{
	director* d = new director(new concrete_builder());
	d->construct();
	return 0;
}
