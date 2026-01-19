#pragma once

#include "algebra3.h"
#include "colour_to_normal.h"
#include "image_decorator.h"

class image_normal_map : public image_decorator
{
public:
  image_normal_map() { m_rot_matrix = alg3::identity2D(); }
 
  image_normal_map(p_image child) : image_decorator(child) { m_rot_matrix = alg3::identity2D(); }

  colour get_colour(int x, int y) const
  {
    const colour& c = m_child->get_colour(x, y);
    alg3::vec3 n = colour_to_normal(c);
    n = m_rot_matrix * n;
    colour res = normal_to_colour(n);
    res.a = c.a; // not sure, pass alpha through unchanged?
    return res;
  }

  void set_rotation(const alg3::mat3& rot_matrix)
  {
    m_rot_matrix = rot_matrix;
  }

private:
  alg3::mat3 m_rot_matrix;
};

