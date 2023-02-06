#include "catch.hpp"
#include "image_32.h"
#include "image_region.h"

namespace
{
colour make_colour(int i)
{
  return colour(i, i, i);
}
}

p_image src_image()
{
  p_image src = std::make_shared<image_32>();

  src->set_size(2, 2);
  src->set_colour(0, 0, make_colour(1));
  src->set_colour(1, 0, make_colour(2));
  src->set_colour(0, 1, make_colour(3));
  src->set_colour(1, 1, make_colour(4));

  return src;
}

TEST_CASE("get_colour: full size region looks like child", "[image_region]")
{
  std::shared_ptr<image_region> ir = std::make_shared<image_region>(src_image());

  REQUIRE(ir->get_width() == 2);
  REQUIRE(ir->get_height() == 2);
  REQUIRE(ir->get_colour(0, 0) == make_colour(1));
  REQUIRE(ir->get_colour(1, 0) == make_colour(2));
  REQUIRE(ir->get_colour(0, 1) == make_colour(3));
  REQUIRE(ir->get_colour(1, 1) == make_colour(4));
}

TEST_CASE("get_colour: Check 1x1 sub region 1", "[image_region]")
{
  std::shared_ptr<image_region> ir = std::make_shared<image_region>(src_image());
  ir->set_region(0, 0, 1, 1);  // top left, 1x1

  REQUIRE(ir->get_width() == 1);
  REQUIRE(ir->get_height() == 1);
  REQUIRE(ir->get_colour(0, 0) == make_colour(1));
}

TEST_CASE("get_colour: Check 1x1 sub region 2", "[image_region]")
{
  std::shared_ptr<image_region> ir = std::make_shared<image_region>(src_image());
  ir->set_region(1, 1, 1, 1);  // lower right, 1x1

  REQUIRE(ir->get_width() == 1);
  REQUIRE(ir->get_height() == 1);
  REQUIRE(ir->get_colour(0, 0) == make_colour(4));
}

TEST_CASE("get_colour: go out of range", "[image_region]")
{
}

TEST_CASE("set_colour: write to 1x1 sub region 1", "[image_region]")
{
  auto src = src_image();
  std::shared_ptr<image_region> ir = std::make_shared<image_region>(src);
  ir->set_region(0, 0, 1, 1);  // top left, 1x1
  ir->set_colour(0, 0, make_colour(5));

  REQUIRE(ir->get_colour(0, 0) == make_colour(5));
  REQUIRE(src->get_colour(0, 0) == make_colour(5));
}

TEST_CASE("set_colour: write to 1x1 sub region 2", "[image_region]")
{
  auto src = src_image();
  std::shared_ptr<image_region> ir = std::make_shared<image_region>(src);
  ir->set_region(1, 1, 1, 1);  // lower right, 1x1
  ir->set_colour(0, 0, make_colour(5));

  REQUIRE(ir->get_colour(0, 0) == make_colour(5));
  REQUIRE(src->get_colour(0, 0) == make_colour(1));
  REQUIRE(src->get_colour(1, 1) == make_colour(5));
}




