#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "kr.hpp"


TEST_CASE("Keyboard Row")
{
	Solution s;
	std::vector<std::string> res={"Alaska","Dad"};
	std::vector<std::string> v1={"Hello","Alaska","Dad","Peace"};
	REQUIRE(s.findWords(v1)==res);
}