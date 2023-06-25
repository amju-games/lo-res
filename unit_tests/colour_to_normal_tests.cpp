#include <iostream>
#include "catch.hpp"
#include "colour_to_normal.h"
#include "approx_equal.h"

TEST_CASE("colour(.5, .5, 1) gives vec (0, 0, 1)", "[colour_to_normal]")
{
  alg3::vec3 n = colour_to_normal(colour(0x80, 0x80, 0xff));
  alg3::vec3 expected =  alg3::vec3(0, 0, 1);
  //std::cout << n << "\n";
  REQUIRE(approx_equal(n, expected, 0.01f));
}

TEST_CASE("colour(.5, .5, .5) gives zero vec", "[colour_to_normal]")
{
  REQUIRE(approx_equal(colour_to_normal(colour(0x80, 0x80, 0x80)), alg3::vec3(0, 0, 0), 0.01f));
}

TEST_CASE("normal(1, 0, 0) gives expected colour (1, .5, .5)", "[normal_to_colour]")
{
  colour c = normal_to_colour({1.f, 0.f, 0.f}); 
  colour expected(0xff, 0x80, 0x80);
  //std::cout << c << "\n";
  REQUIRE(approx_equal(c, expected, 1));
}


