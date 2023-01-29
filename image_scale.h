// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image_decorator.h"

class image_scale : public image_decorator
{
public:
  image_scale() = default;
  image_scale(p_image child, float scale = 1.f)
  {
    m_child = child;
    m_scale = scale;
  }

  void set_scale(float scale) { m_scale = scale; }

  colour get_colour(int u, int v) const override;

  int get_width() const override;
  int get_height() const override;

protected:
  float m_scale;
};

