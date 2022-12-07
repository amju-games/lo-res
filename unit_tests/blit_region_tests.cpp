// "LO RES"
// (c) Copyright 2017 Jason Colman

#include "catch.hpp"
#include "image.h"

// Test blitting regions, especially clipping.

static void setup(image& dest, image& src)
{
  dest.set_size(4, 4);
  dest.clear(0);

  src.set_size(4, 4);

  int c = 1;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      src.set_colour(src.index(j, i), c);
      c++; 
    }
  }

  // Src:
  // 1  2  3  4
  // 5  6  7  8
  // 9  10 11 12
  // 13 14 15 16

  REQUIRE(src.get_colour(src.index(0, 0)) == 1);
  REQUIRE(src.get_colour(src.index(0, 1)) == 5);
  REQUIRE(src.get_colour(src.index(0, 2)) == 9);
}

TEST_CASE("blit region test, no clip", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src region to the middle of 4x4 dest
  src.blit_region(dest, 1, 1,  1, 1, 2, 2); 

  // Expected:
  // 0  0  0  0
  // 0  6  7  0
  // 0  10 11 0
  // 0  0  0  0

  // Outside edge should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(i, 0)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 3)) == 0);
    REQUIRE(dest.get_colour(dest.index(0, i)) == 0);
    REQUIRE(dest.get_colour(dest.index(3, i)) == 0);
  }
  // Centre of dest should have copy of src image
  REQUIRE(dest.get_colour(dest.index(1, 1)) == 6);
  REQUIRE(dest.get_colour(dest.index(2, 1)) == 7);
  REQUIRE(dest.get_colour(dest.index(1, 2)) == 10);
  REQUIRE(dest.get_colour(dest.index(2, 2)) == 11);
}

TEST_CASE("blit region test, clip left", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 region to the left
  src.blit_region(dest, -1, 1,  1, 1, 2, 2); 

  // Expected:
  // 0  0  0  0
  // 7  0  0  0
  // 11 0  0  0
  // 0  0  0  0

  // Rightmost 3 cols should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(1, i)) == 0);
    REQUIRE(dest.get_colour(dest.index(2, i)) == 0);
    REQUIRE(dest.get_colour(dest.index(3, i)) == 0);
  }

  // Left edge
  REQUIRE(dest.get_colour(dest.index(0, 0)) == 0);
  REQUIRE(dest.get_colour(dest.index(0, 1)) == 7);
  REQUIRE(dest.get_colour(dest.index(0, 2)) == 11);
  REQUIRE(dest.get_colour(dest.index(0, 3)) == 0);
}

TEST_CASE("blit region test, clip top", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src above dest
  src.blit_region(dest, 1, -1,  1, 1, 2, 2); 

  // Expected:
  // 0  10 11 0
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0

  // Bottom 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(i, 1)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 2)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 3)) == 0);
  }

  // Top edge
  REQUIRE(dest.get_colour(dest.index(0, 0)) == 0);
  REQUIRE(dest.get_colour(dest.index(1, 0)) == 10);
  REQUIRE(dest.get_colour(dest.index(2, 0)) == 11);
  REQUIRE(dest.get_colour(dest.index(3, 0)) == 0);
}

TEST_CASE("blit region test, clip right", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src to the right
  src.blit_region(dest, 3, 1,  1, 1, 2, 2); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  6 
  // 0  0  0  10
  // 0  0  0  0

  // Leftmost 3 cols should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(0, i)) == 0);
    REQUIRE(dest.get_colour(dest.index(1, i)) == 0);
    REQUIRE(dest.get_colour(dest.index(2, i)) == 0);
  }

  // Right edge
  REQUIRE(dest.get_colour(dest.index(3, 0)) == 0);
  REQUIRE(dest.get_colour(dest.index(3, 1)) == 6);
  REQUIRE(dest.get_colour(dest.index(3, 2)) == 10);
  REQUIRE(dest.get_colour(dest.index(3, 3)) == 0);
}

TEST_CASE("blit region test, clip bottom", "[image]")
{
  image dest;
  image src;
  setup(dest, src);
 
  // Blit 2x2 src below dest
  src.blit_region(dest, 1, 3,  1, 1, 2, 2); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0
  // 0  6  7  0

  // Top 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(i, 0)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 1)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 2)) == 0);
  }

  // Bottom edge
  REQUIRE(dest.get_colour(dest.index(0, 3)) == 0);
  REQUIRE(dest.get_colour(dest.index(1, 3)) == 6);
  REQUIRE(dest.get_colour(dest.index(2, 3)) == 7);
  REQUIRE(dest.get_colour(dest.index(3, 3)) == 0);
}

