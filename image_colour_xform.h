// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "algebra3.h"
#include "colour.h"
#include "image_decorator.h"


// Transform colour of all texels, adding a colour, and multiplying by 0..1 for each
//  component.
// TODO Should we pre- or post-multiply? Should we offer both?
 
class image_colour_xform : public image_decorator
{
public:
  image_colour_xform() = default;
  image_colour_xform(p_image child, const colour& add, const vec4& mult)
  {
    m_child = child;
    m_add = add;
    m_mult = mult;
  }

  colour get_colour(int u, int v) const override;

protected:
  colour m_add = { 0, 0, 0, 0 };
  vec4 m_mult = { 1.f, 1.f, 1.f, 1.f };
};

