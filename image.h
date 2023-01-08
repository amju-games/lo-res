// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include "colour_index.h"
#include "palette.h"

// * image *
// Stores image as a rectangular array of 8-bit indices into a palette of
//  colours. 

using COLOUR_INDEX = unsigned char;

class image
{
public:
  // Pixels with this colour index are transparent, i.e. not copied in
  //  blit operations.
  static const COLOUR_INDEX TRANSPARENT; 

  // * set_size *
  // As an alternative to loading an image from a file, set the size
  //  and set pixel colours.
  void set_size(int w, int h);

  // * load *
  // Load an RGB 24-bit png image.
  // Adds the colours found in the image to the given palette.
  // Stores the image as indices into the palette.
  bool load(const std::string& png_file_name);

  // Set the colour (really a palette index) at the given position index.
  void set_colour(int index, COLOUR_INDEX ch)
  {
    m_data[index] = ch;
  }

  COLOUR_INDEX get_colour(int index) const
  {
    return m_data[index];
  }

  // * index *
  // Convert (x, y) coord into index into data
  int index(int x, int y) const
  {
    assert(x >= 0); 
    assert(y >= 0); 
    assert(x < m_width); 
    assert(y < m_height); 
    return y * m_width + x;
  }

  // * clear *
  // Clear image to the given colour (palette index)
  void clear(COLOUR_INDEX c = 0);

  // * blit *
  // Blit this image to the given destination image, at the given (x, y)
  //  coord in the destination.
  // Pixels with colour index TRANSPARENT are not copied.
  void blit(image& dest, int dest_x, int dest_y) const;
	
  // * blit_region *
  // Blit a rectangular region of this source image to the destination.
  // Pixels with colour index TRANSPARENT are not copied.
  void blit_region(image& dest, int dest_x, int dest_y, 
    int src_x, int src_y, int src_w, int src_h) const;

  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

  static palette& get_palette();

protected:
  int m_width = 0;
  int m_height = 0;

  std::vector<COLOUR_INDEX> m_data;

  static palette m_pal;
};

using p_image = std::shared_ptr<image>;

