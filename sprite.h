// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include "sprite_sheet.h"

class sprite : public sprite_sheet
{
public:
  void draw(image& dest, int dest_x, int dest_y);

  void update(float dt);

  void set_cell_time(float t)
  {
    m_cell_max_time = t;
  }

  void set_cell_range(int min_cell, int max_cell, int dir = 1);

  int get_cell() const { return m_cell; }

protected:
  int m_cell = 0;
  float m_cell_max_time = .1f;
  float m_cell_time = 0.f;
  int m_min_cell = 0;
  int m_max_cell = 0;
  int m_cell_dir = 0;
};

