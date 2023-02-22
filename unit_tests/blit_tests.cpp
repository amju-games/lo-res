// "LO RES"
// (c) Copyright 2017-2022 Juliet Colman

#include "blit.h"
#include "catch.hpp"
#include "image_8.h"
#include "image_32.h"

// Test blitting, especially clipping.

namespace
{
colour make_colour(int i)
{
  return colour(i, i, i);
}
}

void setup(ref_image dest, ref_image src)
{
  dest->set_size(4, 4);
  dest->clear(make_colour(0));
 
  src->set_size(2, 2);
  src->set_colour(0, 0, make_colour(1)); 
  src->set_colour(1, 0, make_colour(2)); 
  src->set_colour(0, 1, make_colour(3)); 
  src->set_colour(1, 1, make_colour(4));
}

void blit_middle(ref_image src, ref_image dest)
{
  // Blit 2x2 src to the middle of 4x4 dest
  blit<overwrite>(src, dest, 1, 1); 

  // Expected:
  // 0  0  0  0
  // 0  1  2  0
  // 0  3  4  0
  // 0  0  0  0

  // Outside edge should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(i, 0) == make_colour(0));
    REQUIRE(dest->get_colour(i, 3) == make_colour(0));
    REQUIRE(dest->get_colour(0, i) == make_colour(0));
    REQUIRE(dest->get_colour(3, i) == make_colour(0));
  }
  // Centre of dest should have copy of src image_8
  REQUIRE(dest->get_colour(1, 1) == make_colour(1));
  REQUIRE(dest->get_colour(2, 1) == make_colour(2));
  REQUIRE(dest->get_colour(1, 2) == make_colour(3));
  REQUIRE(dest->get_colour(2, 2) == make_colour(4));
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
  blit<overwrite>(src, dest, -1, 1); 

  // Expected:
  // 0  0  0  0
  // 2  0  0  0
  // 4  0  0  0
  // 0  0  0  0

  // Rightmost 3 cols should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(1, i) == make_colour(0));
    REQUIRE(dest->get_colour(2, i) == make_colour(0));
    REQUIRE(dest->get_colour(3, i) == make_colour(0));
  }

  // Left edge
  REQUIRE(dest->get_colour(0, 0) == make_colour(0));
  REQUIRE(dest->get_colour(0, 1) == make_colour(2));
  REQUIRE(dest->get_colour(0, 2) == make_colour(4));
  REQUIRE(dest->get_colour(0, 3) == make_colour(0));
}

TEST_CASE("blit test, clip top", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src above dest
  blit<overwrite>(src, dest, 1, -1); 

  // Expected:
  // 0  3  4  0
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0

  // Bottom 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(i, 1) == make_colour(0));
    REQUIRE(dest->get_colour(i, 2) == make_colour(0));
    REQUIRE(dest->get_colour(i, 3) == make_colour(0));
  }

  // Top edge
  REQUIRE(dest->get_colour(0, 0) == make_colour(0));
  REQUIRE(dest->get_colour(1, 0) == make_colour(3));
  REQUIRE(dest->get_colour(2, 0) == make_colour(4));
  REQUIRE(dest->get_colour(3, 0) == make_colour(0));
}

TEST_CASE("blit test, clip right", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src to the right
  blit<overwrite>(src, dest, 3, 1); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  1
  // 0  0  0  3
  // 0  0  0  0

  // Leftmost 3 cols should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(0, i) == make_colour(0));
    REQUIRE(dest->get_colour(1, i) == make_colour(0));
    REQUIRE(dest->get_colour(2, i) == make_colour(0));
  }

  // Right edge
  REQUIRE(dest->get_colour(3, 0) == make_colour(0));
  REQUIRE(dest->get_colour(3, 1) == make_colour(1));
  REQUIRE(dest->get_colour(3, 2) == make_colour(3));
  REQUIRE(dest->get_colour(3, 3) == make_colour(0));
}

TEST_CASE("blit test, clip bottom", "[image_8]")
{
  p_image dest = std::make_shared<image_8>();
  p_image src = std::make_shared<image_8>();
  setup(dest, src);

  // Blit 2x2 src below dest
  blit<overwrite>(src, dest, 1, 3); 

  // Expected:
  // 0  0  0  0
  // 0  0  0  0
  // 0  0  0  0
  // 0  1  2  0

  // Top 3 rows should be zeroes
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(dest->get_colour(i, 0) == make_colour(0));
    REQUIRE(dest->get_colour(i, 1) == make_colour(0));
    REQUIRE(dest->get_colour(i, 2) == make_colour(0));
  }

  // Bottom edge
  REQUIRE(dest->get_colour(0, 3) == make_colour(0));
  REQUIRE(dest->get_colour(1, 3) == make_colour(1));
  REQUIRE(dest->get_colour(2, 3) == make_colour(2));
  REQUIRE(dest->get_colour(3, 3) == make_colour(0));
}

TEST_CASE("blit with subtract", "[blit]")
{
  p_image src = std::make_shared<image_32>();
  p_image dest = std::make_shared<image_32>();
  src->set_size(1, 1);
  src->set_colour(0, 0, colour(6, 5, 4, 3));
  dest->set_size(1, 1);
  dest->set_colour(0, 0, colour(5, 7, 1, 2));
  
  // dest = src - dest
  blit<sub_blend>(src, dest, 0, 0);
  colour result = dest->get_colour(0, 0);
  REQUIRE(result == colour(1, 0, 3, 1));
}



