// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <cassert>
#include <iostream>
#include "sprite.h"

//#define SPRITE_DEBUG

void sprite::draw(ref_image dest, int dest_x, int dest_y) const
{
  draw_cell(dest, m_cell, dest_x, dest_y);
}

void sprite::set_cell_range(int min_cell, int max_cell)
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
      if (m_bounce_mode) // In bounce mode, we change direction when we reach the end of the range.
      {
        m_cell = m_max_cell;
        m_cell_dir = - m_cell_dir;
#ifdef SPRITE_DEBUG
std::cout << "Bounce: max reached (" << m_max_cell << ") new cell: " << m_cell << " dir: " << m_cell_dir << "\n";
#endif
      }
      else
      {
        m_cell = m_min_cell;
      }
    }
    else if (m_cell < m_min_cell)
    {
      if (m_bounce_mode)
      {
        m_cell = m_min_cell;
        m_cell_dir = -m_cell_dir;
#ifdef SPRITE_DEBUG
std::cout << "Bounce: min reached (" << m_min_cell << ") new cell: " << m_cell << " dir: " << m_cell_dir << "\n";
#endif
      }
      else
      {
        m_cell = m_max_cell;
      }
    }
  }
}

