/*#include <gtest/gtest.h>
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <vector>
#include "../../Catch/include/catch.hpp"

std::pair<int,int> ant_time(int L/*Length*/,std::vector<int> N/*number*/)
{
	int minT=0;
	int maxT=0;
	for (auto n:N)
	{
		minT = std::max(minT,std::min(n,L-n));
		maxT = std::max(maxT,std::max(n,L-n));
	}

	return std::make_pair(minT,maxT);
}


TEST_CASE("ants")
{
    auto res = std::make_pair(4,8);
    std::vector<int> v={2,6,7};
    REQUIRE(res==ant_time(10,v));

    auto res2 = std::make_pair(4,9);
    std::vector<int> v2={2,6,7,8,5,9,4};
    REQUIRE(res==ant_time(10,v));
}
