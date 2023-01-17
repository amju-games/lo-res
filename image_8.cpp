// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <algorithm>
#include <cassert>
#include <iostream>
#include "lodepng.h"
#include "image_8.h"

const COLOUR_INDEX image_8::TRANSPARENT = 0;

palette image_8::m_pal;

palette& image_8::get_palette()
{
  return m_pal;
}

bool image_8::load(const std::string& png_file_name)
{
  std::vector<unsigned char> data;
  unsigned int w = 0;
  unsigned int h = 0;
  unsigned nError = lodepng::decode(data, w, h, png_file_name);
  if (nError != 0)
  {
    std::cout << "Failed to load " << png_file_name << "\n";
    return false;
  }

  // Add each RGB colour to palette. Set palette index in data,
  //  not the actual colour.
  int rgb_size = w * h * 4;
  for (int i = 0; i < rgb_size; i += 4)
  {
    int alpha = data[i + 3];
    colour col(data[i], data[i + 1], data[i + 2]);

    const int TRANSPARENT_LIMIT = 128;
    const colour MAGENTA(255, 0, 255);

    if (alpha < TRANSPARENT_LIMIT || col == MAGENTA)
    {
      m_data.push_back(TRANSPARENT);
    }
    else
    {
      int pal_index = m_pal.add_colour(col); 
      assert(pal_index < 0x100);
      char ch = pal_index & 0xff;
      m_data.push_back(ch);
    }
  }

  m_width = w;
  m_height = h;

  return true;
}

bool image_8::is_transparent(int x, int y) const 
{
  return m_data[index(x, y)] == TRANSPARENT;
}

void image_8::set_colour(int x, int y, colour col)
{
  m_data[index(x, y)] = m_pal.get_index(col);
}
  
colour image_8::get_colour(int x, int y) const 
{
  return m_pal.get_colour(m_data[index(x, y)]);
}

void image_8::clear(colour col)
{
  COLOUR_INDEX ci = m_pal.get_index(col);
  std::fill(m_data.begin(), m_data.end(), ci);
}


