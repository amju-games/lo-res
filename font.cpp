// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include "font.h"
#include "screen.h"

void font::draw(image& dest, int dest_x, int dest_y, const std::string& text)
{
  int x = dest_x;
  int y = dest_y; 
  for (char ch : text)
  {
    if (ch == '\n' || x >= screen::WIDTH)
    {
      x = dest_x;
      y += m_cell_h + 1;
    }
    else
    {
      int cell = ch - ' ';
      cell = (cell >= 0 && cell < (m_cells_x * m_cells_y)) ? cell : 0;
      draw_cell(dest, cell, x, y);
      x += m_cell_w;
    }
  }
}

