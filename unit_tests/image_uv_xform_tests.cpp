#include "catch.hpp"
#include "image_8.h"
#include "image_uv_xform.h"

namespace
{
colour make_colour(int i)
{
  return colour(i, i, i);
}

p_image make_sq_image()
{
  p_image im = std::make_shared<image_8>();

  im->set_size(2, 2);
  im->set_colour(0, 0, make_colour(1));
  im->set_colour(1, 0, make_colour(2));
  im->set_colour(0, 1, make_colour(3));
  im->set_colour(1, 1, make_colour(4));

  return im;
}
}

TEST_CASE("transform by identity", "[image_uv_xform]")
{
  p_image im = make_sq_image();
  p_image xf = std::make_shared<image_uv_xform>(im, alg3::identity2D());

  REQUIRE(xf->get_width() == im->get_width());
  REQUIRE(xf->get_height() == im->get_height());
  REQUIRE(xf->get_colour(0, 0) == make_colour(1));
  REQUIRE(xf->get_colour(1, 0) == make_colour(2));
  REQUIRE(xf->get_colour(0, 1) == make_colour(3));
  REQUIRE(xf->get_colour(1, 1) == make_colour(4));
}

TEST_CASE("transform square image by rotation 90 degs", "[image_uv_xform]")
{
  alg3::vec2 centre_of_rot(.5f, .5f); // needs to be (w-1)/2, (h-1)/2?
  float angle_degs = 90.f;
  alg3::mat3 m = rotation2D(centre_of_rot, angle_degs);

  p_image im = make_sq_image();
  p_image xf = std::make_shared<image_uv_xform>(im, m);

  REQUIRE(im->get_width() == 2);
  REQUIRE(xf->get_width() == im->get_width()); // same because rotating a square
  REQUIRE(xf->get_height() == im->get_height());

  // Square rotated 90 degs CW
  REQUIRE(xf->get_colour(0, 0) == make_colour(3));
  REQUIRE(xf->get_colour(1, 0) == make_colour(1));
  REQUIRE(xf->get_colour(0, 1) == make_colour(4));
  REQUIRE(xf->get_colour(1, 1) == make_colour(2));
}
