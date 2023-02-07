#include "catch.hpp"
#include "filler.h"
#include "image_32.h"

TEST_CASE("fill with solid colour", "[filler]")
{
  p_image im = std::make_shared<image_32>();
  im->set_size(1, 1);
  fill(im, solid_colour(colour(0xff, 0, 0)));
  REQUIRE(im->get_colour(0, 0) == colour(0xff, 0, 0));
}

TEST_CASE("fill with block colour, use lambda", "[filler]")
{
  p_image im = std::make_shared<image_32>();
  im->set_size(1, 1);
  fill(im, [](int, int, int, int) { return colour(0xff, 0, 0); });
  REQUIRE(im->get_colour(0, 0) == colour(0xff, 0, 0));
}

TEST_CASE("fill with noise", "[filler]")
{
  p_image im = std::make_shared<image_32>();
  im->set_size(1, 1);
  fill(im, noise());

  // How to test!?
  //REQUIRE(im->get_colour(0, 0) == colour(0xff, 0, 0));
}

