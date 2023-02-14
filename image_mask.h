#pragma once

#include "transparency.h"
#include "image_composite.h"

// Child image[0] is src image
// Child image[1] is mask, which selects non-transparent texels in the src
template<class IS_TRANSPARENT = zero_alpha>
class image_mask : public image_composite
{
public:
  image_mask() { m_active_child = 0; }

  image_mask(p_image src, p_image mask)
  {
    add_child(src);
    add_child(mask);
  }

  void set_transparent_colour(const colour& c) { m_transparent_colour = c; }
 
  colour get_colour(int x, int y) const override
  {
    IS_TRANSPARENT is_transparent;
    if (is_transparent(m_children[1]->get_colour(x, y)))
    {
      return m_transparent_colour;
    }
    return m_children[0]->get_colour(x, y);
  }

private:
  colour m_transparent_colour = {0, 0, 0, 0};
};

