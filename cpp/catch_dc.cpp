#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "dc.hpp"


TEST_CASE("575_Distribute_Candies")
{
	Solution s;
	std::vector<int> v1={1,1,2,2,3,3};
	REQUIRE(s.dc(v1)==3);

	std::vector<int> v2={1,1,1,1,1,3};
	REQUIRE(s.dc(v2)==2);

	std::vector<int> v3={1,1};
	REQUIRE(s.dc(v3)==1);

	std::vector<int> v4={1,1,2,3};
	REQUIRE(s.dc(v4)==2);

	std::vector<int> v5={1,4,2,3,5,6,7,1};
	REQUIRE(s.dc(v5)==4);

	std::vector<int> v6={1,1,1,1,2,2,2,2};
	REQUIRE(s.dc(v6)==2);
}