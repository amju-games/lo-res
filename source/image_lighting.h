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
    dot = std::clamp(dot, 0.f, 1.f);

    f_colour diffuse_col = m_diffuse_colour * dot;
    diffuse_col.a = m_diffuse_colour.a; //c.a; // * dot?

    float sp = std::clamp(powf(dot, m_spec_power), 0.f, 1.f);
    f_colour spec_col = m_specular_colour * sp;
    spec_col.a = m_specular_colour.a * sp; //c.a; // right?

    f_colour final = m_ambient_colour + diffuse_col + spec_col;
    final.a *= static_cast<float>(c.a) / 255.f;
    colour result = final.to_colour();
    ////result.a *= c.a; // riiight?????
    return result;
  }

  void set_light_dir(const alg3::vec3& light_dir) { m_light_dir = light_dir; m_light_dir.normalize(); }

  void set_ambient_colour(const colour& c) { m_ambient_colour = c; }
  void set_diffuse_colour(const colour& c) { m_diffuse_colour = c; }
  void set_specular_colour(const colour& c) { m_specular_colour = c; }
  void set_specular_power(float p) { m_spec_power = p; }

private:
  alg3::vec3 m_light_dir { .707f, .707f, 0.707f };
  f_colour m_ambient_colour { 0, 0, 0, 1 };
  f_colour m_diffuse_colour { .5f, .5f, .5f, 1 };
  f_colour m_specular_colour { 1, 1, 1, 1 };
  float m_spec_power = 100.f;
};

