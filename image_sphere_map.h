#pragma once

#include "colour_to_normal.h"
#include "image_composite.h"

// Child image[0] is a normal map. 
// Child image[1] is spherical env map.
class image_sphere_map : public image_composite
{
public:
  image_sphere_map() { m_active_child = 1; }

  colour get_colour(int x, int y) const override
  {
    const colour& c = m_children[0]->get_colour(x, y);
    alg3::vec3 n = colour_to_normal(c);
    n[alg3::VZ] += 1.f;
    n.normalize();
    float x1 = n[alg3::VX] * .5f + .5f;
    float y1 = n[alg3::VY] * .5f + .5f;
    const auto& im = m_children[1];
    return im->get_colour(x1 * im->get_width(), y1 * im->get_height()); 
  }
};

