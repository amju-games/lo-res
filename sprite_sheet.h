// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <cassert>
#include "image.h"

// Result of pixel intersection test
enum class pix_int_result
{
  YES_COLLIDE,
  NO_AND_DISJOINT, // the two sprites do not overlap
  NO_AND_NOT_DISJOINT // sprites overlap but no pairs of opaque pixels
};

class sprite_sheet 
{
public:
  void set_image(const p_image& image) { m_image = image; }
  p_image get_image() { return m_image; }
  const p_image& get_image() const { return m_image; }

  void draw_cell(ref_image dest, int cell, int dest_x, int dest_y) const;

  void set_num_cells(int x, int y)
  {
    assert(m_image.get()); // set image first

    m_cells_x = x;
    m_cells_y = y;
    m_cell_w = m_image->get_width() / m_cells_x;
    m_cell_h = m_image->get_height() / m_cells_y;
  }

  int get_cell_w() const { return m_cell_w; }
  int get_cell_h() const { return m_cell_h; }

  friend pix_int_result pixel_intersect(
    const sprite_sheet& ss1, int cell1, int x1, int y1,
    const sprite_sheet& ss2, int cell2, int x2, int y2);

protected:
  p_image m_image;

  int m_cells_x = 1;
  int m_cells_y = 1;
  int m_cell_w = 1;
  int m_cell_h = 1;
};

