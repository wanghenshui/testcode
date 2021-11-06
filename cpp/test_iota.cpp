#define CATCH_CONFIG_MAIN
#include "../../../Catch/include/catch.hpp"
#include "iota.hpp"
#include "count.hpp"

TEST_CASE("a[i]= value+1")
{
	int a[5];
	for (int i = 0; i < count(a); ++i)
	{
		iota(a,i,i);
		REQUIRE(a[i]==i+i);
	}
}