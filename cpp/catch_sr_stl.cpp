#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "sr_stl.hpp"
#include <iostream>

TEST_CASE("Search for a Range with STL")
{
	Solution s;

	std::vector<int> v1={1,1,2,2,3,3};
	std::vector<int> ans1_1={0,1},ans1_2={2,3},ans1_3={4,5};
	REQUIRE(s.searchRange(v1,2)==ans1_2);
	REQUIRE(s.searchRange(v1,1)==ans1_1);
	REQUIRE(s.searchRange(v1,3)==ans1_3);
	std::vector<int> v2={-1};
	std::vector<int> ans2={0,0};
	REQUIRE(s.searchRange(v2,-1)==ans2);
	std::vector<int> v3={5,7,7,8,8,10};
	std::vector<int> ans3_1={3,4},ans3_2={5,5};
	REQUIRE(s.searchRange(v3,8)==ans3_1);
	REQUIRE(s.searchRange(v3,10)==ans3_2);

	std::vector<int> v4={},ans4={-1,-1};
	REQUIRE(s.searchRange(v2,0)==ans4);
	for(auto i :s.searchRange(v2,0))
		std::cout<<i<<std::endl;
	REQUIRE(s.searchRange(v4,0)==ans4);
}