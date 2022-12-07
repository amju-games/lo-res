// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include "image.h"

class sprite_sheet : public image
{
public:
  void draw_cell(image& dest, int cell, int dest_x, int dest_y);

  void set_num_cells(int x, int y)
  {
    m_cells_x = x;
    m_cells_y = y;
  }

protected:
  int m_cells_x = 1;
  int m_cells_y = 1;
};

