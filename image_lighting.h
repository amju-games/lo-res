#pragma once

#include "colour_to_normal.h"
#include "image_decorator.h"

// Child image is a normal map. 
class image_lighting : public image_decorator
{
public:
  image_lighting() = default;
  image_lighting(p_image child) : image_decorator(child) {}

  colour get_colour(int x, int y) const override
  {
    const colour& c = m_child->get_colour(x, y);
    alg3::vec3 n = colour_to_normal(c);
    float dot = n * m_light_dir;
    float d = std::clamp(dot + powf(dot, 1000.f), 0.f, 1.f);
    return colour_from_floats(d, d, d);
  }

  void set_light_dir(const alg3::vec3& light_dir) { m_light_dir = light_dir; m_light_dir.normalize(); }

private:
  alg3::vec3 m_light_dir { .707f, .707f, 0.707f };
};

