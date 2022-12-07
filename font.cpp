// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include "font.h"
#include "screen.h"

void font::draw(image& dest, int dest_x, int dest_y, const std::string& text)
{
  int cell_w = m_width / m_cells_x;
  int cell_h = m_height / m_cells_y;

  int x = dest_x;
  int y = dest_y; 
  for (char ch : text)
  {
    if (ch == '\n' || x >= screen::WIDTH)
    {
      x = dest_x;
      y += cell_h + 1;
    }
    else
    {
      draw_cell(dest, ch - ' ', x, y);
      x += cell_w;
    }
  }
}

