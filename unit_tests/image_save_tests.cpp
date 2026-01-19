#include "catch.hpp"
#include "filler.h"
#include "image_32.h"

TEST_CASE("save image", "[image_32]")
{
  auto im = std::make_shared<image_32>();
  im->set_size(64, 64);
  fill(im, solid_colour(colour(0xff, 0x80, 0x10, 0x40)));
  bool ok = im->save("saved-image.png");
  REQUIRE(ok);
}

