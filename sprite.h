// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "blit.h"
#include "sprite_sheet.h"

class sprite : public sprite_sheet
{
public:
  template<class BLENDER>
  void draw(ref_image dest, int dest_x, int dest_y) const
  {
    draw_cell<BLENDER>(dest, m_cell, dest_x, dest_y);
  }

  void update(float dt);

  void set_cell_time(float t)
  {
    m_cell_max_time = t;
  }

  void set_cell_range(int min_cell, int max_cell);
  void set_cell(int cell) { m_cell = cell; }

  void set_cell_dir(int dir) { m_cell_dir = dir; }

  int get_cell() const { return m_cell; }
  
  // In bounce mode, the cell dir flips when we reach the end of the range.
  void set_bounce_mode(bool bm) { m_bounce_mode = bm; }

protected:
  int m_cell = 0;
  float m_cell_max_time = .1f;
  float m_cell_time = 0.f;
  int m_min_cell = 0;
  int m_max_cell = 0;
  int m_cell_dir = 1;
  bool m_bounce_mode = false;
};

