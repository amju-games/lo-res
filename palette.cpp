// "LO RES" Game Prototype
// (c) Jason Colman 2017

#include <iostream>
#include <cassert>
#include "image.h"
#include "palette.h"

palette::palette()
{
  m_colours.reserve(256);
  // Colour zero is for TRANSPARENT index - using MAGENTA
  m_colours.push_back(colour(255, 0, 255));
}

int palette::add_colour(const colour& col)
{
  auto it = std::find(m_colours.begin(), m_colours.end(), col);
  if (it != m_colours.end())
  {
    return std::distance(m_colours.begin(), it);
  }
  m_colours.push_back(col);

  std::cout << "Adding colour to palette: " 
    << (unsigned int)col.r << ", " 
    << (unsigned int)col.g << ", " 
    << (unsigned int)col.b << "\n";

  return m_colours.size() - 1;
}

const colour& palette::get_colour(int c) const
{
  assert(c < m_colours.size());
  return m_colours[c];
}

