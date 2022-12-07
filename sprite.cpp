// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include <cassert>
#include "sprite.h"

void sprite::draw(image& dest, int dest_x, int dest_y)
{
  draw_cell(dest, m_cell, dest_x, dest_y);
}

void sprite::set_cell_range(int min_cell, int max_cell, int dir)
{
  if (m_cell < min_cell)
  {   
    m_cell = min_cell; 
  }   

  if (m_cell > max_cell)
  {   
    m_cell = max_cell;
  }   

  m_min_cell = min_cell;
  m_max_cell = max_cell;
  m_cell_dir = dir;
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

