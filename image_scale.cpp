// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <algorithm>
#include "image_scale.h"

colour image_scale::get_colour(int u, int v) const
{
  float su = static_cast<float>(u) / m_scale_x;
  float sv = static_cast<float>(v) / m_scale_y;
  return m_child->get_colour(su, sv);
}

int image_scale::get_width() const 
{
  return m_scale_x * m_child->get_width();
}

int image_scale::get_height() const 
{
  return m_scale_y * m_child->get_height();
}

