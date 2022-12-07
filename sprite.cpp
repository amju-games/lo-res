// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include <cassert>
#include "sprite.h"

void sprite::draw(image& dest, int dest_x, int dest_y)
{
  draw_cell(dest, m_cell, dest_x, dest_y);
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

