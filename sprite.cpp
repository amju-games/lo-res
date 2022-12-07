// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include <cassert>
#include "sprite.h"

void sprite::draw(image& dest, int dest_x, int dest_y)
{
  // Draw cell at pos on screen
  // Calc cell x, y, w, h

  int cell_w = m_width / m_cells_x;
  int cell_h = m_height / m_cells_y;

  // Get top left of current cell (m_cell)
  assert(m_cell < m_cells_x * m_cells_y);
  int cell_x = m_cell % m_cells_x * cell_w;
  int cell_y = m_cell / m_cells_x * cell_h;

  blit_region(dest, dest_x, dest_y,
    cell_x, cell_y, cell_w, cell_h,
    0 /* m_transparent_key */);
}

void sprite::update(float dt)
{
  m_cell_time += dt;
  if (m_cell_time > m_cell_max_time)
  {
    m_cell_time -= m_cell_max_time;
    m_cell += m_cell_dir;
    if (m_cell > m_max_cell)
    {
      m_cell = m_min_cell;
    }
  }
}

