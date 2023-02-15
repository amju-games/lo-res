// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image_decorator.h"

class image_scale : public image_decorator
{
public:
  image_scale() = default;

  image_scale(p_image child)
  {
    m_child = child;
  }

  image_scale(p_image child, float scale)
  {
    m_child = child;
    set_scale(scale);
  }

  image_scale(p_image child, float scale_x, float scale_y)
  {
    m_child = child;
    set_scale(scale_x, scale_y);
  }

  void set_scale(float scale) { set_scale(scale, scale); }

  void set_scale(float scale_x, float scale_y) 
  { 
    m_scale_x = scale_x;
    m_scale_y = scale_y; 
  }

  colour get_colour(int u, int v) const override;

  int get_width() const override;
  int get_height() const override;

protected:
  float m_scale_x = 1.f;
  float m_scale_y = 1.f;
};

