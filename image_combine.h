#pragma once

#include "blend.h"
#include "image_composite.h"

class image_combine : public image_composite
{
public:
  image_combine(p_image image1, p_image image2, blend_func bf)
  {
    add_child(image1);
    add_child(image2);
    m_blend_func = bf;
  }

  image_combine(blend_func bf)
  {
    m_blend_func = bf;
  }

  colour get_colour(int x, int y) const override
  {
    colour c1 = m_children[0]->get_colour(x, y);
    for (int i = 1; i < m_children.size(); i++)
    {
      const colour& c2 = m_children[i]->get_colour(x, y);
      c1 = m_blend_func(c1, c2);
    }
    return c1;
  }

protected:
  blend_func m_blend_func;
};

