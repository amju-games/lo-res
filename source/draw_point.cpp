#include <cmath>
#include "draw_point.h"

void draw_point(ref_image dest, int x, int y, const colour& c)
{
  if (x >= 0 && x < dest->get_width() && y >= 0 && y < dest->get_height())
  {
    dest->set_colour(x, y, c);
  }
}

