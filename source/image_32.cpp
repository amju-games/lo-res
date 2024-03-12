// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <cassert>
#include <iostream>
#include "lodepng.h"
#include "image_32.h"

bool image_32::load(const std::string& png_file_name)
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

  assert(data.size() == w * h * 4);
  m_data = data; 

  m_width = w;
  m_height = h;

  return true;
}

colour image_32::get_colour(int x, int y) const 
{
  int i = index(x, y);
  return colour(m_data[i], m_data[i + 1], m_data[i + 2], m_data[i + 3]);
}

void image_32::set_colour(int x, int y, colour c)
{
  int i = index(x, y);
  m_data[i]     = c.r;
  m_data[i + 1] = c.g;
  m_data[i + 2] = c.b;
  m_data[i + 3] = c.a;
}

void image_32::clear(colour c) 
{
  int s = get_width() * get_height() * 4;
  for (int i = 0; i < s; i += 4)
  {
    m_data[i]     = c.r;
    m_data[i + 1] = c.g;
    m_data[i + 2] = c.b;
    m_data[i + 3] = c.a;
  }
}

