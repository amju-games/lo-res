// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <algorithm>
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
  // * set_size *
  // As an alternative to loading an image from a file, set the size
  //  and then you can set pixel colours.
  void set_size(int w, int h) override
  {
    m_width = w;
    m_height = h;
    m_data.resize(w * h * N);
  }

  // Set the colour or palette index at the given position index.
  void set_colour(int x, int y, COLOUR_INDEX ch) override
  {
    m_data[index(x, y)] = ch;
  }

  COLOUR_INDEX get_colour(int x, int y) const override
  {
    return m_data[index(x, y)];
  }

  // * clear *
  // Clear image to the given value
  void clear(COLOUR_INDEX c = 0) override
  {
    std::fill(m_data.begin(), m_data.end(), c);
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

