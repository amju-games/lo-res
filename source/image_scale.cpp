// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <algorithm>
#include "image_scale.h"

colour image_scale::get_colour(int u, int v) const
{
  float su = static_cast<float>(u) / m_scale_x;
  float sv = static_cast<float>(v) / m_scale_y;
  return m_child->get_colour(static_cast<int>(su), static_cast<int>(sv));
}

int image_scale::get_width() const 
{
  return static_cast<int>(m_scale_x * static_cast<float>(m_child->get_width()));
}

int image_scale::get_height() const 
{
  return static_cast<int>(m_scale_y * static_cast<float>(m_child->get_height()));
}

