// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image.h"

void blit(const_ref_image src, ref_image dest, int dest_x, int dest_y);

// * blit_region *
// Blit a rectangular region of the source image to the destination.
// Transparent pixels are not copied.
void blit_region(
  const_ref_image src,
  ref_image dest, 
  int dest_x, int dest_y, // use uv type
  int src_x, int src_y, 
  int src_w, int src_h); // use size type


