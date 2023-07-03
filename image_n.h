// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include "image.h"
#include "palette.h"

// * image_n *
// Stores image as a rectangular array of colours, each colour represented
//  by N unsigned ints.

template<int N>
class image_n : public image
{
public:
  image_n() = default;

  image_n(int w, int h)
  {
    set_size(w, h);
  }

  // * set_size *
  // As an alternative to loading an image from a file, set the size
  //  and then you can set pixel colours.
  void set_size(int w, int h) override
  {
    m_width = w;
    m_height = h;
    m_data.resize(w * h * N);
  }

  int get_width() const override { return m_width; }
  int get_height() const override { return m_height; }

protected:
  // * index *
  // Convert (x, y) coord into index into data
  int index(int x, int y) const
  {
    assert(x >= 0);
    assert(y >= 0);
    assert(x < m_width);
    assert(y < m_height);
    return N * (y * m_width + x);
  }

protected:
  std::vector<uint8_t> m_data;

  int m_width = 0;
  int m_height = 0;
};

