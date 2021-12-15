#define CATCH_CONFIG_MAIN
#include "s2d.hpp"
#include <catch.hpp>
#include <iostream>

TEST_CASE(" search 2d")
{
	Solution s;

	REQUIRE(s.searchMatrix({ {2} }, 2) == 1);
	std::cin.get();
}
