#define CATCH_CONFIG_MAIN
#include "../../../Catch/include/catch.hpp"
#include "mismatch.hpp"


TEST_CASE("mismatch")
{
	double a[5]={1.0,2.0,3.0,4.0,5.0};
	double b[5]={1.0,2.1,3.0,4.0,5.0};
	double c[5]={1.0,2.0,3.0,4.0,5.1};
	REQUIRE(mismatch(a,b,5)==1);
	REQUIRE(mismatch(a,c,5)==4);
}