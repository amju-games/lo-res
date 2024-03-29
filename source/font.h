// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "sprite_sheet.h"

class font : public sprite_sheet
{
public:
  template<class BLENDER>
  void draw(ref_image dest, int dest_x, int dest_y, const std::string& text)
  {
    int x = dest_x;
    int y = dest_y;
    for (char ch : text)
    {
      if (ch == '\n')
      {
        x = dest_x;
        y += m_cell_h + 1;
      }
      else
      {
        int cell = ch - ' ';
        cell = (cell >= 0 && cell < (m_cells_x * m_cells_y)) ? cell : 0;
        draw_cell<BLENDER>(dest, cell, x, y);
        x += m_cell_w;
      }
    }
  }
};

