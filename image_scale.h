// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image_decorator.h"

class image_scale : public image_decorator
{
public:
  image_scale() = default;
  image_scale(p_image child, float scale_x = 1.f, float scale_y = 1.f)
  {
    m_child = child;
    m_scale_x = scale_x;
    m_scale_y = scale_y;
  }

  void set_scale(float scale) { m_scale_x = m_scale_y = scale; }
  void set_scale(float scale_x, float scale_y) 
  { 
    m_scale_x = scale_x;
    m_scale_y = scale_y; 
  }

  colour get_colour(int u, int v) const override;

  int get_width() const override;
  int get_height() const override;

protected:
  float m_scale_x;
  float m_scale_y;
};

