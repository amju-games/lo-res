// "LO RES"
// (c) Copyright 2017-2022 Juliet Colman

#include "blit.h"
#include "catch.hpp"
#include "image_8.h"

// Test blitting, especially clipping.

void setup(ref_image dest, ref_image src)
{
  dest->set_size(4, 4);
  dest->clear(0);
 
  src->set_size(2, 2);
  src->set_colour(0, 0, 1); 
  src->set_colour(1, 0, 2); 
  src->set_colour(0, 1, 3); 
  src->set_colour(1, 1, 4);
}

void blit_middle(ref_image src, ref_image dest)
{
  // Blit 2x2 src to the middle of 4x4 dest
  blit(src, dest, 1, 1); 

  // Expected:
  // 0  0  0  0
  // 0  1  2  0
  // 0  3  4  0
  // 0  0  0  0

  // Outside edge should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(i, 0) == 0);
    REQUIRE(dest->get_colour(i, 3) == 0);
    REQUIRE(dest->get_colour(0, i) == 0);
    REQUIRE(dest->get_colour(3, i) == 0);
  }
  // Centre of dest should have copy of src image_8
  REQUIRE(dest->get_colour(1, 1) == 1);
  REQUIRE(dest->get_colour(2, 1) == 2);
  REQUIRE(dest->get_colour(1, 2) == 3);
  REQUIRE(dest->get_colour(2, 2) == 4);
}

TEST_CASE("blit test, no clip", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);
  blit_middle(src, dest);
}

TEST_CASE("blit test, clip left", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src to the left
  blit(src, dest, -1, 1); 

  // Expected:
  // 0  0  0  0
  // 2  0  0  0
  // 4  0  0  0
  // 0  0  0  0

  // Rightmost 3 cols should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(1, i) == 0);
    REQUIRE(dest->get_colour(2, i) == 0);
    REQUIRE(dest->get_colour(3, i) == 0);
  }

  // Left edge
  REQUIRE(dest->get_colour(0, 0) == 0);
  REQUIRE(dest->get_colour(0, 1) == 2);
  REQUIRE(dest->get_colour(0, 2) == 4);
  REQUIRE(dest->get_colour(0, 3) == 0);
}

TEST_CASE("blit test, clip top", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src above dest
  blit(src, dest, 1, -1); 

  // Expected:
  // 0  3  4  0
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0

  // Bottom 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(i, 1) == 0);
    REQUIRE(dest->get_colour(i, 2) == 0);
    REQUIRE(dest->get_colour(i, 3) == 0);
  }

  // Top edge
  REQUIRE(dest->get_colour(0, 0) == 0);
  REQUIRE(dest->get_colour(1, 0) == 3);
  REQUIRE(dest->get_colour(2, 0) == 4);
  REQUIRE(dest->get_colour(3, 0) == 0);
}

TEST_CASE("blit test, clip right", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src to the right
  blit(src, dest, 3, 1); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  1
  // 0  0  0  3
  // 0  0  0  0

  // Leftmost 3 cols should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(0, i) == 0);
    REQUIRE(dest->get_colour(1, i) == 0);
    REQUIRE(dest->get_colour(2, i) == 0);
  }

  // Right edge
  REQUIRE(dest->get_colour(3, 0) == 0);
  REQUIRE(dest->get_colour(3, 1) == 1);
  REQUIRE(dest->get_colour(3, 2) == 3);
  REQUIRE(dest->get_colour(3, 3) == 0);
}

TEST_CASE("blit test, clip bottom", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src below dest
  blit(src, dest, 1, 3); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0
  // 0  1  2  0

  // Top 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(i, 0) == 0);
    REQUIRE(dest->get_colour(i, 1) == 0);
    REQUIRE(dest->get_colour(i, 2) == 0);
  }

  // Bottom edge
  REQUIRE(dest->get_colour(0, 3) == 0);
  REQUIRE(dest->get_colour(1, 3) == 1);
  REQUIRE(dest->get_colour(2, 3) == 2);
  REQUIRE(dest->get_colour(3, 3) == 0);
}

