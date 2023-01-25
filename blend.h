// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image.h"
#include "transparency.h"

// Useful blend operations to use as BLENDER type in blit functions

// Just overwrites the dest with what's in the src. Like blending is disabled.

struct overwrite
{
  void operator()(
    const_ref_image src,
    ref_image dest,
    int x, int y,
    int src_x, int src_y,
    int dest_x, int dest_y)
  {
    const auto& src_col = src->get_colour(x + src_x, y + src_y);
    dest->set_colour(x + dest_x, y + dest_y, src_col);
  }
};


// Pixel mask: src pixels satisfying the transparency test are not copied to dest. 

template<class IS_TRANSPARENT>
struct mask
{
  void operator()(
    const_ref_image src,
    ref_image dest,
    int x, int y,
    int src_x, int src_y,
    int dest_x, int dest_y)
  {
    IS_TRANSPARENT is_transparent;

    const auto& src_col = src->get_colour(x + src_x, y + src_y);
    if (!is_transparent(src_col))
    { 
      dest->set_colour(x + dest_x, y + dest_y, src_col);
    }
  }
};

using mask_zero_alpha = mask<zero_alpha>;


struct additive_blend
{
  colour calc_additive_blend(const colour& src, const colour& dest)
  {
    // TODO Should use alpha here?
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
    auto dest_col = dest->get_colour(x + dest_x, y + dest_y);
    auto result = calc_additive_blend(src_col, dest_col);
    dest->set_colour(x + dest_x, y + dest_y, result);
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
    auto dest_col = dest->get_colour(x + dest_x, y + dest_y);
    auto result = calc_alpha_blend(src_col, dest_col);
    dest->set_colour(x + dest_x, y + dest_y, result);
  }
};

