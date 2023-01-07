// "LO RES"
// (c) Copyright 2017-2022 Juliet Colman

#include "catch.hpp"
#include "sprite_sheet.h"

// Test pixel-perfect intersection between two sprite sheets.

class pixel_fixture
{
public:
  pixel_fixture()
  {
    image1 = std::make_shared<image>();
    image2 = std::make_shared<image>();
    image1->set_size(W, H);
    image2->set_size(W, H);
    ss1.set_image(image1);
    ss2.set_image(image2);
    
    set_all_cells_transparent();
  }

protected:
  void set_all_cells_transparent();
  void test_overlap_transparent(int c1, int c2) const;

  static void set_cell_opaque(sprite_sheet& ss, int cell);

  static constexpr int W = 4;
  static constexpr int H = 2;
  static constexpr int OPAQUE = 1;

  sprite_sheet ss1, ss2;
  p_image image1, image2;
};

void pixel_fixture::set_all_cells_transparent()
{
  // Set all pixels to transparent to start
  for (int x = 0; x < W; x++)
  {
    for (int y = 0; y < H; y++)
    { 
      ss1.get_image()->set_colour(ss1.get_image()->index(x, y), image::TRANSPARENT);
      ss2.get_image()->set_colour(ss2.get_image()->index(x, y), image::TRANSPARENT);
    }
  }
  ss1.set_num_cells(2, 1);
  ss2.set_num_cells(2, 1);
}

void pixel_fixture::set_cell_opaque(sprite_sheet& ss, int cell)
{
  int CELL_W = 2, CELL_H = 2;
  for (int x = 0; x < CELL_W; x++)
  {
    for (int y = 0; y < CELL_H; y++)
    {
      ss.get_image()->set_colour(ss.get_image()->index(x + cell * CELL_W, y), OPAQUE);
    }
  }
}

TEST_CASE_METHOD(pixel_fixture, "pixel test - disjoint in x", "[sprite_sheet]")
{
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

TEST_CASE_METHOD(pixel_fixture, "pixel test - disjoint in y", "[sprite_sheet]")
{
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

void pixel_fixture::test_overlap_transparent(int c1, int c2) const
{
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

TEST_CASE_METHOD(pixel_fixture, "pixel test - overlap transparent", "[sprite_sheet]")
{
  test_overlap_transparent(0, 0); // cells in sprite 1 and 2
  test_overlap_transparent(1, 0);
  test_overlap_transparent(0, 1);
  test_overlap_transparent(1, 1);
}

