// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <cmath>
#include "colour.h"
#include "image_filter.h"

colour image_filter::get_colour(int x, int y) const
{
  h_colour res;

  float total_weight = 0;

  // The basic idea is res += (m_child->get_colour(uv(x, y) + offset) * weight;
  // Then we divide by number of elements at the end.

  const float w = get_width();
  const float h = get_height();
  for (auto [offset, weight] : m_filter)
  {
    uv pos = offset + uv(x, y);
    if (pos.u >= 0 && pos.v >= 0 && pos.u < w && pos.v < h)
    {
      total_weight += weight;

      res += h_colour(m_child->get_colour(pos.u, pos.v)) * weight;
    }
  }

  const float EPSILON = 0.001f;
  if (fabs(total_weight) > EPSILON)
  {
    res *= (1.f / total_weight);
  }
  return res.to_colour();
}

