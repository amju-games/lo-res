#include <iostream>
#include "approx_equal.h"
#include "catch.hpp"
#include "image_32.h"
#include "image_lighting.h"

TEST_CASE("1-pixel image gives dot product of colour-as-normal", "[image_lighting]")
{
  p_image normal_map = std::make_shared<image_32>();
  normal_map->set_size(1, 1);
  colour cn = normal_to_colour({1, 0, 0});
  normal_map->set_colour(0, 0, cn);

  auto lighting = std::make_shared<image_lighting>(normal_map);
  lighting->set_light_dir({1.f, 0.f, 0.f});

  colour expected(0xff, 0xff, 0xff);
  colour c = lighting->get_colour(0, 0);
  std::cout << "Lighting result: " << c << "\n";

  // TODO result is 2/256 off - where are we losing precision?
  REQUIRE(approx_equal(c, expected, 3));
}

