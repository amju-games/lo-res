#ifdef XF_DEBUG
#include <iostream>
#endif

#include "image_uv_xform.h"


std::shared_ptr<image_uv_xform> make_scale_xform(float uniform_scale)
{
  return make_scale_xform(uniform_scale, uniform_scale);
}

std::shared_ptr<image_uv_xform> make_scale_xform(float scale_x, float scale_y)
{
  mat3 m = scaling2D(vec2(scale_x, scale_y));
  auto xf = std::make_shared<image_uv_xform>();
  xf->set_xform(m);
  return xf;
}

std::shared_ptr<image_uv_xform> make_rotate_xform(float angle_degs)
{
  vec2 centre_of_rot(.5f, .5f); // needs to be (w-1)/2, (h-1)/2?
  mat3 m = rotation2D(centre_of_rot, angle_degs);

  auto xf = std::make_shared<image_uv_xform>();
  xf->set_xform(m);
  return xf;
}

colour image_uv_xform::get_colour(int u, int v) const
{
  const float w = m_child->get_width();
  const float h = m_child->get_height();

  const float Z = 1.0f;

  vec3 vec = m_inverse * vec3(u, v, Z);

#ifdef XF_DEBUG
std::cout << "get_colour: input uv: " << vec3(u, v, Z) << " -> ";
std::cout << "output uv: " << vec ;
#endif

  int u1 = static_cast<int>(vec[0]); // round down
  int v1 = static_cast<int>(vec[1]);

  if (u1 < 0 || v1 < 0 || u1 >= w || v1 >= h)
  {
std::cout << "get_colour: input uv: " << vec3(u, v, Z) << " -> ";
std::cout << "output uv: " << vec ;
std::cout << ": get_colour() uv is out of range (" << w << ", " << h << ").\n";
    return colour(0, 0, 0, 0);
  } 

  colour c =  m_child->get_colour(u1, v1);

#ifdef XF_DEBUG
std::cout << "  colour: " << (int)c.r << "\n";
#endif

  return c;
}

int image_uv_xform::get_width() const 
{
  auto ZERO_TRANSLATION = 0;
  vec3 v = m_matrix * vec3(m_child->get_width(), m_child->get_height(), ZERO_TRANSLATION);
#ifdef XF_DEBUG
std::cout << "xformed size: " << v << "\n";
#endif
  double d = fabs(round(v[0]));
  return d;
}

int image_uv_xform::get_height() const 
{
  auto ZERO_TRANSLATION = 0;
  vec3 v = m_matrix * vec3(m_child->get_width(), m_child->get_height(), ZERO_TRANSLATION);
#ifdef XF_DEBUG
std::cout << "xformed size: " << v << "\n";
#endif
  double d = fabs(round(v[1]));
  return d;
}

