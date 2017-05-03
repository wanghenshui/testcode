#define CATCH_CONFIG_MAIN
#include "../../../Catch/include/catch.hpp"
#include "inner_product.hpp"
#include "fill.hpp"
#include "count.hpp"

TEST_CASE("inner_product")
{

	int a[5] ,b[5];
	fill(a,0,5,2);
	fill(b,0,5,7);
	int n=count(a);
	REQUIRE(inner_product(a,b,n)==70);

	int c[65536] ,d[65536];
	fill(c,0,65536,1);
	fill(d,0,65536,1);
	n=count(c);
	REQUIRE(inner_product(c,d,n)==65536);
}