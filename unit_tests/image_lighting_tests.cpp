#include "catch.hpp"
#include "image_32.h"
#include "image_lighting.h"

TEST_CASE("1-pixel image gives dot product of colour-as-normal", "[image_lighting]")
{
  p_image normal_map = std::make_shared<image_32>();
  normal_map->set_size(1, 1);
  normal_map->set_colour(0, 0, colour(0xff, 0x80, 0x80)); // normal (1, 0, 0)

  auto lighting = std::make_shared<image_lighting>(normal_map);
  lighting->set_light_dir({1.f, 0.f, 0.f});

  REQUIRE(lighting->get_colour(0, 0).r == 0xff); // r, g, b components the same 
}

