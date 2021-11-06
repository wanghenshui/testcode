#define CATCH_CONFIG_MAIN
#include "../../../Catch/include/catch.hpp"
#include "fill.hpp"
const int MAX=100;
TEST_CASE("fill")
{
	int a[MAX];
	fill(a,2,90,4);
	double b[MAX];
	fill(b,4,47,2.2);


	REQUIRE(a[89]==a[2]);
	REQUIRE(a[56]==4);
	REQUIRE(b[44]==b[4]);
	REQUIRE(b[46]==2.2);
}