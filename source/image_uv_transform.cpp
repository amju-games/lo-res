// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

//#define XF_DEBUG

#ifdef XF_DEBUG
#include <iostream>
#endif

#include "image_uv_transform.h"

/*
std::shared_ptr<image_uv_transform> make_scale_transform(float uniform_scale)
{
  return make_scale_transform(uniform_scale, uniform_scale);
}

std::shared_ptr<image_uv_transform> make_scale_transform(float scale_x, float scale_y)
{
  alg3::mat3 m = scaling2D(alg3::vec2(scale_x, scale_y));
  auto xf = std::make_shared<image_uv_transform>();
  xf->set_transform(m);
  return xf;
}
*/

alg3::mat3 make_rot_around_centre_matrix(const p_image im, float angle_degs)
{
  alg3::vec2 centre_of_rot(im->get_width() / 2, im->get_height() / 2);
  return rotation2D(centre_of_rot, angle_degs);
}

std::shared_ptr<image_uv_transform> make_rotate_transform(p_image im, float angle_degs)
{
  auto xf = std::make_shared<image_uv_transform>();
  xf->set_transform(make_rot_around_centre_matrix(im, angle_degs));
  xf->set_child(im);
  return xf;
}

colour image_uv_transform::get_colour(int u, int v) const
{
  const float w = static_cast<float>(m_child->get_width());
  const float h = static_cast<float>(m_child->get_height());

  const float Z = 1.0f;

  alg3::vec3 vec = m_inverse * alg3::vec3(static_cast<float>(u), static_cast<float>(v), Z);

#ifdef XF_DEBUG
std::cout << "get_colour: input uv: " << alg3::vec3(u, v, Z) << " -> ";
std::cout << "output uv: " << vec << "\n";
#endif

  int u1 = static_cast<int>(vec[0]); // round down
  int v1 = static_cast<int>(vec[1]);

  if (u1 < 0 || v1 < 0 || u1 >= w || v1 >= h)
  {
#ifdef XF_DEBUG
std::cout << "get_colour: input uv: " << alg3::vec3(u, v, Z) << " -> ";
std::cout << "output uv: " << vec ;
std::cout << ": get_colour() uv is out of range (" << w << ", " << h << ").\n";
#endif
    return colour(1, 1, 1, 1);
  } 

  colour c =  m_child->get_colour(u1, v1);

#ifdef XF_DEBUG
std::cout << "  colour: " << (int)c.r << "\n";
#endif

  return c;
}

int image_uv_transform::get_width() const 
{
  float w = static_cast<float>(m_child->get_width());
  float h = static_cast<float>(m_child->get_height());
  float w1 = m_matrix[0][0] * w;
  float w2 = m_matrix[0][1] * h;
  float ret = fabs(w1) + fabs(w2);
#ifdef XF_DEBUG
std::cout << "w: " << w << " h: " << h << " w1: " << w1 << " w2: " << w2 << " ret: " << ret << "\n";
#endif

  return static_cast<int>(ret);
}

int image_uv_transform::get_height() const 
{
  float w = static_cast<float>(m_child->get_width());
  float h = static_cast<float>(m_child->get_height());
  float h1 = m_matrix[1][0] * w;
  float h2 = m_matrix[1][1] * h;
  float ret = fabs(h1) + fabs(h2);
#ifdef XF_DEBUG
std::cout << "w: " << w << " h: " << h << " h1: " << h1 << " h2: " << h2 << " ret: " << ret << "\n";
#endif
  return ret;
}

