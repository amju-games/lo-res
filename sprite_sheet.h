// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image.h"

// Result of pixel intersection test
enum class pix_int_result
{
  YES_COLLIDE,
  NO_AND_DISJOINT, // the two sprites do not overlap
  NO_AND_NOT_DISJOINT // sprites overlap but no pairs of opaque pixels
};

class sprite_sheet : public image
{
public:
  void draw_cell(image& dest, int cell, int dest_x, int dest_y);

  void set_num_cells(int x, int y)
  {
    m_cells_x = x;
    m_cells_y = y;
  }

  friend pix_int_result pixel_intersect(
    const sprite_sheet& ss1, int cell1, int x1, int y1,
    const sprite_sheet& ss2, int cell2, int x2, int y2);

protected:
  int m_cells_x = 1;
  int m_cells_y = 1;
};

