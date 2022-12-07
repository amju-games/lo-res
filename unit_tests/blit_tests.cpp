// "LO RES"
// (c) Copyright 2017 Jason Colman

#include "catch.hpp"
#include "image.h"

TEST_CASE("blit tests", "[image]")
{
  // Test blitting, especially clipping.
  image dest;
  dest.set_size(4, 4);
  dest.clear(0);
 
  image src;
  src.set_size(2, 2);
  src.set_colour(src.index(0, 0), 1); 
  src.set_colour(src.index(1, 0), 2); 
  src.set_colour(src.index(0, 1), 3); 
  src.set_colour(src.index(1, 1), 4);

  // Blit 2x2 src to the middle of 4x4 dest
  src.blit(dest, 1, 1); 
  // Outside edge should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(i, 0)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 3)) == 0);
    REQUIRE(dest.get_colour(dest.index(0, i)) == 0);
    REQUIRE(dest.get_colour(dest.index(3, i)) == 0);
  }
}

