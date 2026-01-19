#pragma once

#include "colour_to_normal.h"
#include "image_composite.h"

// Child image[0] is a normal map. 
// Child image[1] is spherical env map.
class image_sphere_map : public image_composite
{
public:
  image_sphere_map() { m_active_child = 0; }

  image_sphere_map(p_image normal_map, p_image env_map)
  {
    add_child(normal_map);
    add_child(env_map);
    m_active_child = 0;
  }

  colour get_colour(int x, int y) const override
  {
    const colour& c = m_children[0]->get_colour(x, y);
    alg3::vec3 n = colour_to_normal(c);
    n[alg3::VZ] += 1.f;
    n.normalize();
    float x1 = n[alg3::VX] * .5f + .5f;
    float y1 = n[alg3::VY] * .5f + .5f;
    const auto& im = m_children[1];
    int w = im->get_width();
    int h = im->get_height();
    int x_clamped = std::clamp(static_cast<int>(x1 * w), 0, w - 1);
    int y_clamped = std::clamp(static_cast<int>(y1 * h), 0, h - 1);
    colour res = im->get_colour(x_clamped, y_clamped);
    res.a = c.a; // TODO Mult, in 0..1 space
    return res;
  }
};

