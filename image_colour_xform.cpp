// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include "image_colour_xform.h"

colour image_colour_xform::get_colour(int u, int v) const 
{
  h_colour c = m_child->get_colour(u, v);
  c.r *= m_mult[0];
  c.g *= m_mult[1];  
  c.b *= m_mult[2];  
  c.a *= m_mult[3];
  c += m_add;
  return c.to_colour();  
}

