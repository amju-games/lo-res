// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include "sprite.h"

void sprite::draw(image& dest)
{
  // Draw cell at pos on screen
  // Calc cell x, y, w, h

  blit(dest, (int)m_pos.x, (int)m_pos.y, 0);
}

void sprite::update(float dt)
{
  vec2 old_vel = m_vel;
  m_vel += m_acc * dt;
  m_pos += (old_vel + m_vel) * (.5f * dt);

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

