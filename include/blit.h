// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

// Blit/blit region with blend functions. Using template functors for the blend
//  functions, so hopefully faster than passing functions in.

#include "blend.h"
#include "image.h"

// * blit_region *
// Blit a rectangular region of the source image to the destination.
template<class BLENDER>
void blit_region(
  const_ref_image src,
  ref_image dest, 
  int dest_x, int dest_y, // use uv type?
  int src_x, int src_y, 
  int src_w, int src_h)  // use size type?
{
  // Don't blit pixels which are off the left hand edge of dest.
  int x_min = std::max(0, -dest_x);

  // Don't blit pixels which are off the right hand edge of dest.
  int x_max = std::min(src_w, dest->get_width() - dest_x);

  // Same for top and bottom
  int y_min = std::max(0, -dest_y);
  int y_max = std::min(src_h, dest->get_height() - dest_y);

  BLENDER blender;

  // Blit the region of the src image which intersects the destination
  //  image.

  // NB we scan horizontally for cache-friendliness!
  for (int y = y_min; y < y_max; y++)
  {
    for (int x = x_min; x < x_max; x++)
    {
      blender(src, dest, x, y, src_x, src_y, dest_x, dest_y);
    }
  }
}

template<class BLENDER>
void blit(const_ref_image src, ref_image dest, int dest_x, int dest_y)
{
  blit_region<BLENDER>(src, dest, dest_x, dest_y, 0, 0, src->get_width(), src->get_height());
}


