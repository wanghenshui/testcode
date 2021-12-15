#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "SiRSA.hpp"


TEST_CASE("SiRSA")
{
	Solution s;
	std::vector<int> v1={1,1,2,2,3,3};
	REQUIRE(s.search(v1,1)==6);

	std::vector<int> v2={1,1,1,1,1,3};
	REQUIRE(s.arrayPairSum(v2)==3);
}