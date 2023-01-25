// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

// Blit/blit region with blend functions. Using template functors for the blend
//  functions, so hopefully faster than passing functions in.

#include "image.h"

struct no_blend
{
  void operator()(
    const_ref_image src, 
    ref_image dest, 
    int x, int y, 
    int src_x, int src_y, 
    int dest_x, int dest_y)
  {
    auto src_col = src->get_colour(x + src_x, y + src_y);
    if (!src_col.is_transparent())
    {
      dest->set_colour(x + dest_x, y + dest_y, src_col);
    }
  }
};

struct additive_blend
{
  colour calc_additive_blend(const colour& src, const colour& dest)
  {
    h_colour hc = h_colour(src) + h_colour(dest);
    colour result = hc.to_colour();
    result.a = 0xff;
    return result;
  }

  void operator()(
    const_ref_image src, 
    ref_image dest, 
    int x, int y, 
    int src_x, int src_y, 
    int dest_x, int dest_y)
  {
    auto src_col = src->get_colour(x + src_x, y + src_y);
    if (!src_col.is_transparent())
    {
      auto dest_col = dest->get_colour(x + dest_x, y + dest_y);
      auto result = calc_additive_blend(src_col, dest_col);
      dest->set_colour(x + dest_x, y + dest_y, result);
    }
  }
};

struct alpha_blend
{
  colour calc_alpha_blend(const colour& src, const colour& dest)
  {
    // Like (SRC_ALPHA, ONE_MINUS_SRC_ALPHA)
    h_colour hc = 
      h_colour(src) * static_cast<float>(src.a) * (1.f/255.f) +
      h_colour(dest) * (1.f - static_cast<float>(src.a) * (1.f/255.f));
    colour result = hc.to_colour();
    result.a = 0xff;
    return result;
  }

  void operator()(
    const_ref_image src, 
    ref_image dest, 
    int x, int y, 
    int src_x, int src_y, 
    int dest_x, int dest_y)
  {
    auto src_col = src->get_colour(x + src_x, y + src_y);
    if (!src_col.is_transparent()) // TODO is it quicker to just not have this branch?
    {
      auto dest_col = dest->get_colour(x + dest_x, y + dest_y);
      auto result = calc_alpha_blend(src_col, dest_col);
      dest->set_colour(x + dest_x, y + dest_y, result);
    }
  }
};

template<class BLENDER = no_blend>
void blit(const_ref_image src, ref_image dest, int dest_x, int dest_y, BLENDER blender = no_blend())
{
  blit_region(src, dest, dest_x, dest_y, 0, 0, src->get_width(), src->get_height(), blender);
}

// * blit_region *
// Blit a rectangular region of the source image to the destination.
// Transparent pixels are not copied.
template<class BLENDER = no_blend>
void blit_region(
  const_ref_image src,
  ref_image dest, 
  int dest_x, int dest_y, // use uv type?
  int src_x, int src_y, 
  int src_w, int src_h,  // use size type?
  BLENDER blender = no_blend())
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
      blender(src, dest, x, y, src_x, src_y, dest_x, dest_y);
    }
  }
}

