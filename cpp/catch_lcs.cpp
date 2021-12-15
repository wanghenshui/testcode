#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "lcs.hpp"


TEST_CASE("Longest Consecutive Sequence")
{
    Solution s;
    std::vector<int> n1={100,4,200,1,3,2};
    REQUIRE(4==s.longestConsecutive(n1));
}