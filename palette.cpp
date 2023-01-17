// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

//#define PALETTE_DEBUG

#ifdef PALETTE_DEBUG
#include <iostream>
#include "colour.h"

namespace
{
std::ostream& operator<<(std::ostream& os, const colour& col)
{
  return os << "(" 
    << static_cast<int>(col.r) << ", " 
    << static_cast<int>(col.g) << ", " 
    << static_cast<int>(col.b) << ", "
    << static_cast<int>(col.a)
    << ")";
}
}

#endif

#include <cassert>
#include "image.h"
#include "palette.h"

palette::palette()
{
  m_colours.reserve(256);
  // Colour zero is for TRANSPARENT index - using MAGENTA
  m_colours.push_back(colour(255, 0, 255));
}

COLOUR_INDEX palette::get_index(const colour& col) const
{
  // Transparent pixel? 
  if (col.a < 128)
  {
    return 0;
  }

  auto it = std::find(m_colours.begin(), m_colours.end(), col);
  if (it == m_colours.end())
  {
#ifdef PALETTE_DEBUG
std::cout << "palette::get_index: failed to find colour " << col << "\n";
#endif
    assert(false); 
    return 0;
  }
  return std::distance(m_colours.begin(), it);
}

int palette::add_colour(const colour& col)
{
  if (col.a < 128)
  {
    return 0;
  }

  auto it = std::find(m_colours.begin(), m_colours.end(), col);
  if (it != m_colours.end())
  {
    return std::distance(m_colours.begin(), it);
  }
  m_colours.push_back(col);

#ifdef PALETTE_DEBUG
  std::cout << "palette::add_colour: Adding colour to palette: "  << col << "\n";
#endif

  return m_colours.size() - 1;
}

const colour& palette::get_colour(COLOUR_INDEX c) const
{
#ifdef PALETTE_DEBUG
  std::cout << "Getting colour for index: " << static_cast<int>(c) << "\n";
#endif
 
  assert(c < m_colours.size());
  return m_colours[c];
}

