// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include "image_colour_xform.h"

colour image_colour_xform::get_colour(int u, int v) const 
{
  h_colour c = m_child->get_colour(u, v);
  c.r *= m_mult.r;
  c.g *= m_mult.g;  
  c.b *= m_mult.b;  
  c.a *= m_mult.a;
  c += m_add;
  return c.to_colour();  
}

