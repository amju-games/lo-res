// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include "image.h"
#include "vec2.h"

class sprite : public image
{
public:
  void draw(image& dest);

  void update(float dt);

  void set_num_cells(int x, int y)
  {
    m_cells_x = x;
    m_cells_y = y;
  }

  void set_cell_time(float t)
  {
    m_cell_max_time = t;
  }

  void set_cell_range(int min_cell, int max_cell, int dir = 1)
  {
    m_min_cell = min_cell;
    m_max_cell = max_cell;
    m_cell_dir = dir;
  }

  void set_pos(const vec2& pos) { m_pos = pos; }
  void set_vel(const vec2& vel) { m_vel = vel; }
  void set_acc(const vec2& acc) { m_acc = acc; }
 
protected:
  vec2 m_pos;
  vec2 m_vel;
  vec2 m_acc;   
  int m_cell = 0;
  int m_cells_x = 1;
  int m_cells_y = 1;
  float m_cell_max_time = .1f;
  float m_cell_time = 0.f;
  int m_min_cell = 0;
  int m_max_cell = 0;
  int m_cell_dir = 0;
};

