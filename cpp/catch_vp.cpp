#define CATCH_CONFIG_MAIN
#include "../../Catch/include/catch.hpp"
#include "vp.hpp"


TEST_CASE("Valid Parentheses")
{
    Solution s;
    string s1="";
    string s2="(";
    string s3="}";
    string s4="({)}";
    string s5="x";
    string s6="wtf";
    string s7="({[({{[]}})]})";


    REQUIRE(s.isValid(s1));
    REQUIRE(!s.isValid(s2));
    REQUIRE(!s.isValid(s3));
    REQUIRE(!s.isValid(s4));
    REQUIRE(!s.isValid(s5));
    REQUIRE(!s.isValid(s6));
    REQUIRE(s.isValid(s7));
}