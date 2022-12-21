// "LO RES"
// (c) Copyright 2017-2022 Juliet Colman

#include "catch.hpp"
#include "image.h"

// Test blitting, especially clipping.

void setup(image& dest, image& src)
{
  dest.set_size(4, 4);
  dest.clear(0);
 
  src.set_size(2, 2);
  src.set_colour(src.index(0, 0), 1); 
  src.set_colour(src.index(1, 0), 2); 
  src.set_colour(src.index(0, 1), 3); 
  src.set_colour(src.index(1, 1), 4);
}

TEST_CASE("blit test, no clip", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src to the middle of 4x4 dest
  src.blit(dest, 1, 1); 

  // Expected:
  // 0  0  0  0
  // 0  1  2  0
  // 0  3  4  0
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
  REQUIRE(dest.get_colour(dest.index(1, 1)) == 1);
  REQUIRE(dest.get_colour(dest.index(2, 1)) == 2);
  REQUIRE(dest.get_colour(dest.index(1, 2)) == 3);
  REQUIRE(dest.get_colour(dest.index(2, 2)) == 4);
}

TEST_CASE("blit test, clip left", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src to the left
  src.blit(dest, -1, 1); 

  // Expected:
  // 0  0  0  0
  // 2  0  0  0
  // 4  0  0  0
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
  REQUIRE(dest.get_colour(dest.index(0, 1)) == 2);
  REQUIRE(dest.get_colour(dest.index(0, 2)) == 4);
  REQUIRE(dest.get_colour(dest.index(0, 3)) == 0);
}

TEST_CASE("blit test, clip top", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src above dest
  src.blit(dest, 1, -1); 

  // Expected:
  // 0  3  4  0
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
  REQUIRE(dest.get_colour(dest.index(1, 0)) == 3);
  REQUIRE(dest.get_colour(dest.index(2, 0)) == 4);
  REQUIRE(dest.get_colour(dest.index(3, 0)) == 0);
}

TEST_CASE("blit test, clip right", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src to the right
  src.blit(dest, 3, 1); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  1
  // 0  0  0  3
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
  REQUIRE(dest.get_colour(dest.index(3, 1)) == 1);
  REQUIRE(dest.get_colour(dest.index(3, 2)) == 3);
  REQUIRE(dest.get_colour(dest.index(3, 3)) == 0);
}

TEST_CASE("blit test, clip bottom", "[image]")
{
  image dest;
  image src;
  setup(dest, src);

  // Blit 2x2 src below dest
  src.blit(dest, 1, 3); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0
  // 0  1  2  0

  // Top 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest.get_colour(dest.index(i, 0)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 1)) == 0);
    REQUIRE(dest.get_colour(dest.index(i, 2)) == 0);
  }

  // Bottom edge
  REQUIRE(dest.get_colour(dest.index(0, 3)) == 0);
  REQUIRE(dest.get_colour(dest.index(1, 3)) == 1);
  REQUIRE(dest.get_colour(dest.index(2, 3)) == 2);
  REQUIRE(dest.get_colour(dest.index(3, 3)) == 0);
}

