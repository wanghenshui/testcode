#define CATCH_CONFIG_MAIN
#include "../../../Catch/include/catch.hpp"
#include "count.hpp"

int int_array[5];
double double_array[7];

class myclass
{
	int t;
};
myclass myclass_array[8];

TEST_CASE("array number")
{
	REQUIRE(count(int_array)==5);
	REQUIRE(count(double_array)==7);
	REQUIRE(count(myclass_array)==8);
	REQUIRE(count(myclass_array)==9);
}