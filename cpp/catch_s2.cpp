#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "SiRSAII.hpp"


TEST_CASE("Search in Rotated Sorted Array II")
{
    Solution s;

    std::vector<int> n1 ={1,3,1,1,1};
    REQUIRE(s.search(n1,3));
    REQUIRE(s.search(n1,1));
    REQUIRE(!s.search(n1,0));

    std::vector<int> n2;
    REQUIRE(!s.search(n2,0));
    
    std::vector<int> n3 ={1,3};
    REQUIRE(s.search(n3,1));
    REQUIRE(!s.search(n3,0));
    //特殊的用例？


}