// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include "colour_index.h"

// * image *

class image;

using p_image = std::shared_ptr<image>;

// It's safe to pass p_images around but more efficient to use ref_image when we don't
//  care about incrementing the ref count, and can be sure that the ref count won't hit
//  zero while we're doing stuff. 
using ref_image = p_image&;

class image
{
public:
  virtual ~image() = default;

  // * set_size *
  // As an alternative to loading an image from a file, set the size
  //  and set pixel colours.
  virtual void set_size(int w, int h) = 0;

  // * load *
  // Load an RGB 24-bit png image.
  // Adds the colours found in the image to the given palette.
  // Stores the image as indices into the palette.
  virtual bool load(const std::string& png_file_name) = 0;

  // Set the colour (really a palette index) at the given position index.
  virtual void set_colour(int x, int y, COLOUR_INDEX ch) = 0;

  virtual COLOUR_INDEX get_colour(int x, int y) const = 0;

  virtual bool is_transparent(int x, int y) const = 0;

  // * clear *
  // Clear image to the given colour (palette index)
  virtual void clear(COLOUR_INDEX c = 0) = 0;

  // * blit *
  // Blit this image to the given destination image, at the given (x, y)
  //  coord in the destination.
  // Pixels with colour index TRANSPARENT are not copied.
  virtual void blit(ref_image dest, int dest_x, int dest_y) const = 0;
	
  // * blit_region *
  // Blit a rectangular region of this source image to the destination.
  // Pixels with colour index TRANSPARENT are not copied.
  virtual void blit_region(ref_image dest, int dest_x, int dest_y, 
    int src_x, int src_y, int src_w, int src_h) const = 0;

  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

protected:
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

protected:
  int m_width = 0;
  int m_height = 0;
};

