// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include "image.h"

class sprite : public image
{
public:
  void draw(image& dest, int dest_x, int dest_y);

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

protected:
  int m_cell = 0;
  int m_cells_x = 1;
  int m_cells_y = 1;
  float m_cell_max_time = .1f;
  float m_cell_time = 0.f;
  int m_min_cell = 0;
  int m_max_cell = 0;
  int m_cell_dir = 0;
};

