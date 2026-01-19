#pragma once

#include "image.h"

struct solid_colour
{
  solid_colour(const colour& c) : m_colour(c) {}
  colour operator()(int x, int y, int w, int h) { return m_colour; }
  colour m_colour;
};

struct noise_colour
{
  colour operator()(int x, int y, int w, int h)
  {
    return colour(rand() & 0xff, rand() & 0xff, rand() & 0xff, 0xff);
  }
};

struct noise_greyscale
{
  colour operator()(int x, int y, int w, int h)
  {
    int n = rand() & 0xff;
    return colour(n, n, n, 0xff);
  }
};

template<class FILLER>
void fill(p_image im, FILLER f)
{
  int w = im->get_width();
  int h = im->get_height();

  // NB we scan horizontally for cache-friendliness!
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      im->set_colour(x, y, f(x, y, w, h));
    }
  }
}

