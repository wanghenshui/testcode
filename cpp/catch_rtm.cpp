#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "rtm.hpp"


TEST_CASE("Reshape the Matrix")
{
	Solution s;
	std::vector<int> v1={1,1,2,2,3,3};
	REQUIRE(s.arrayPairSum(v1)==6);

	std::vector<int> v2={1,1,1,1,1,3};
	REQUIRE(s.arrayPairSum(v2)==3);

	std::vector<int> v3={1,1};
	REQUIRE(s.arrayPairSum(v3)==1);

	std::vector<int> v4={1,1,2,3};
	REQUIRE(s.arrayPairSum(v4)==3);

	std::vector<int> v5={1,4,2,3,5,6,7,1};
	REQUIRE(s.arrayPairSum(v5)==13);

	std::vector<int> v6={1,1,1,1,2,2,2,2};
	REQUIRE(s.arrayPairSum(v6)==6);
}