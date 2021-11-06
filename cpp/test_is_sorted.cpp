#define CATCH_CONFIG_MAIN
#include "../../../Catch/include/catch.hpp"
#include "is_sorted.hpp"

TEST_CASE("order")
{
	int a[]={0,4,3};
	int b[]={1,1};
	int c[]={1,2,3,4,5};

	REQUIRE(!is_sorted(a,&a[3]));
	REQUIRE(is_sorted(b,&b[2]));
	REQUIRE(is_sorted(c,&c[5]));
}