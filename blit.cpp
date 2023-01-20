// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include "blit.h"

void blit(const_ref_image src, ref_image dest, int dest_x, int dest_y)
{
  blit_region(src, dest, dest_x, dest_y, 0, 0, src->get_width(), src->get_height());
}

void blit_region(
  const_ref_image src,
  ref_image dest,
  int dest_x, int dest_y, // use uv type
  int src_x, int src_y,
  int src_w, int src_h) // use size type
{
  // Don't blit pixels which are off the left hand edge of dest.
  int x_min = std::max(0, -dest_x);

  // Don't blit pixels which are off the right hand edge of dest.
  int x_max = std::min(src_w, dest->get_width() - dest_x);

  // Same for top and bottom
  int y_min = std::max(0, -dest_y);
  int y_max = std::min(src_h, dest->get_height() - dest_y);

  // Blit the region of the src image which intersects the destination
  //  image.
  for (int x = x_min; x < x_max; x++)
  {
    for (int y = y_min; y < y_max; y++)
    {
      auto src_col = src->get_colour(x + src_x, y + src_y);
      if (!src_col.is_transparent())
      {
        //auto dest_col = get_colour(x + dest_x, y + dest_y);

        // TODO Blending here, like
        //   auto result = blend(src_col, dest_col);
        dest->set_colour(x + dest_x, y + dest_y, src_col);
      }
    }
  }
}

