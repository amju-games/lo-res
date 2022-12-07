// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include <string>
#include <vector>
#include "palette.h"

// * image *
// Base class for screen, sprites
class image
{
public:
  void set_size(int w, int h)
  {
    m_width = w;
    m_height = h;
    m_data.resize(w * h);
  }

  // * load *
  // Load an RGB 24-bit png image.
  // Adds the colours found in the image to the given palette.
  // Stores the image as indices into the palette.
  bool load(const std::string& png_file_name, palette& pal);

  // Set the colour (really a palette index) at the given position index.
  void set_colour(int index, char ch)
  {
    m_data[index] = ch;
  }

  char get_colour(int index) const
  {
    return m_data[index];
  }

  // * index *
  // Convert (x, y) coord into index into data
  int index(int x, int y) const;

  // * clear *
  // Clear image to the given colour (palette index)
  void clear(char c = 0)
  {
    for (char& ch : m_data)
    {
      ch = c;
    }
  }

  // * blit *
  // Blit this image to the given destination image, at the given (x, y)
  //  coord in the destination.
  // Pixels with the same colour index as 'transparent' are not copied.
  void blit(image& dest, int dest_x, int dest_y, char transparent);

protected:
  int m_width = 0;
  int m_height = 0;

  std::vector<char> m_data;
};

