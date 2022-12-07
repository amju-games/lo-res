// "LO RES"
// (c) Copyright 2017 Jason Colman

#include "catch.hpp"
#include "sprite_sheet.h"

// Test pixel intersection

const int W = 4;
const int H = 2;
const int OPAQUE = 1;

void setup_transparent(sprite_sheet& ss1, sprite_sheet& ss2)
{
  ss1.set_size(W, H);
  ss2.set_size(W, H);
  // Set all pixels to transparent to start
  for (int x = 0; x < W; x++)
  {
    for (int y = 0; y < H; y++)
    { 
      ss1.set_colour(ss1.index(x, y), image::TRANSPARENT);
      ss2.set_colour(ss2.index(x, y), image::TRANSPARENT);
    }
  }
  ss1.set_num_cells(2, 1);
  ss2.set_num_cells(2, 1);
}

void set_cell_opaque(sprite_sheet& ss, int cell)
{
  int CELL_W = 2, CELL_H = 2;
  for (int x = 0; x < CELL_W; x++)
  {
    for (int y = 0; y < CELL_H; y++)
    {
      ss.set_colour(ss.index(x + cell * CELL_W, y), OPAQUE);
    }
  }
}

TEST_CASE("pixel test - disjoint in x", "[sprite_sheet]")
{
  sprite_sheet ss1, ss2;
  setup_transparent(ss1, ss2);

  int x = 13, y = 17; // some arbitrary position
  
  REQUIRE(pixel_intersect(ss1, 0, x, y, ss2, 0, x + 2, y) == 
    pix_int_result::NO_AND_DISJOINT);

  REQUIRE(pixel_intersect(ss1, 0, x, y, ss2, 0, x - 2, y) == 
    pix_int_result::NO_AND_DISJOINT);

  REQUIRE(pixel_intersect(ss1, 0, x + 2, y, ss2, 0, x, y) == 
    pix_int_result::NO_AND_DISJOINT);

  REQUIRE(pixel_intersect(ss1, 0, x - 2, y, ss2, 0, x, y) == 
    pix_int_result::NO_AND_DISJOINT);
}

TEST_CASE("pixel test - disjoint in y", "[sprite_sheet]")
{
  sprite_sheet ss1, ss2;
  setup_transparent(ss1, ss2);

  int x = -13, y = 17; // some arbitrary position
  
  REQUIRE(pixel_intersect(ss1, 0, x, y, ss2, 0, x, y + 2) == 
    pix_int_result::NO_AND_DISJOINT);

  REQUIRE(pixel_intersect(ss1, 0, x, y, ss2, 0, x, y - 2) == 
    pix_int_result::NO_AND_DISJOINT);

  REQUIRE(pixel_intersect(ss1, 0, x, y + 2, ss2, 0, x, y) == 
    pix_int_result::NO_AND_DISJOINT);

  REQUIRE(pixel_intersect(ss1, 0, x, y - 2, ss2, 0, x, y) == 
    pix_int_result::NO_AND_DISJOINT);
}

void test_overlap_transparent(int c1, int c2)
{
  sprite_sheet ss1, ss2;
  setup_transparent(ss1, ss2);

  int x = 13, y = -17; // some arbitrary position
  
  REQUIRE(pixel_intersect(ss1, c1, x, y, ss2, c2, x + 1, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x, y, ss2, c2, x - 1, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x, y, ss2, c2, x, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x, y, ss2, c2, x, y + 1) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x, y, ss2, c2, x, y - 1) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x + 1, y, ss2, c2, x, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x - 1, y, ss2, c2, x, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x, y + 1, ss2, c2, x, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);

  REQUIRE(pixel_intersect(ss1, c1, x, y - 1, ss2, c2, x, y) == 
    pix_int_result::NO_AND_NOT_DISJOINT);
}

TEST_CASE("pixel test - overlap transparent", "[sprite_sheet]")
{
  test_overlap_transparent(0, 0); // cells in sprite 1 and 2
  test_overlap_transparent(1, 0);
  test_overlap_transparent(0, 1);
  test_overlap_transparent(1, 1);
}

