#pragma once

#include "image_decorator.h"

class image_region : public image_decorator
{
public:
  image_region() = default;
  image_region(p_image child) : image_decorator(child)
  {
    set_region(0, 0, child->get_width(), child->get_height());
  }

  void set_region(int x, int y, int w, int h)
  {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
  }

  int get_width() const override { return m_w; }
  int get_height() const override { return m_h; }

  colour get_colour(int x, int y) const override
  {
    return m_child->get_colour(x + m_x, y + m_y);
  }

  void set_colour(int x, int y, colour c) override
  {
    m_child->set_colour(x + m_x, y + m_y, c);
  }
 
private:
  int m_x = 0;
  int m_y = 0;
  int m_w = 0;
  int m_h = 0;
};

