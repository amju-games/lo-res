#include "catch.hpp"
#include "colour_to_normal.h"

/*
TEST_CASE("black gives zero vec", "[colour_to_normal]")
{
  REQUIRE(colour_to_normal(colour(0, 0, 0)) == alg3::vec3(0, 0, 0));
}

TEST_CASE("colour(.5, .5, 1) gives vec (0, 0, 1)", "[colour_to_normal]")
{
  REQUIRE(colour_to_normal(colour(0x80, 0x80, 0xff)) == alg3::vec3(0, 0, 1));
}
*/

TEST_CASE("colour(.5, .5, .5) gives zero vec", "[colour_to_normal]")
{
  REQUIRE(colour_to_normal(colour(0x80, 0x80, 0x80)) == alg3::vec3(0, 0, 0));
}

TEST_CASE("normal(1, 0, 0) gives expected colour (1, .5, .5)", "[normal_to_colour]")
{
  REQUIRE(normal_to_colour({1.f, 0.f, 0.f}) == colour(0xff, 0x80, 0x80));
}


