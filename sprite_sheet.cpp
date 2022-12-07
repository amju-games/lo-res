// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include <cassert>
#include "sprite_sheet.h"

void sprite_sheet::draw_cell(image& dest, int cell, int dest_x, int dest_y)
{
  // Draw cell at pos on screen
  // Calc cell x, y, w, h

  int cell_w = m_width / m_cells_x;
  int cell_h = m_height / m_cells_y;

  // Get top left of current cell (m_cell)
  assert(cell < m_cells_x * m_cells_y);
  int cell_x = cell % m_cells_x * cell_w;
  int cell_y = cell / m_cells_x * cell_h;

  blit_region(dest, dest_x, dest_y,
    cell_x, cell_y, cell_w, cell_h);
}

