// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include "image.h"
#include "palette.h"

// * image_8 *
// Stores image as a rectangular array of 8-bit indices into a palette of
//  colours. 


class image_8 : public image
{
public:
  // Pixels with this colour index are transparent, i.e. not copied in
  //  blit operations.
  static const COLOUR_INDEX TRANSPARENT; 

  // * set_size *
  // As an alternative to loading an image from a file, set the size
  //  and set pixel colours.
  void set_size(int w, int h) override;

  // * load *
  // Load an RGB 24-bit png image.
  // Adds the colours found in the image to the given palette.
  // Stores the image as indices into the palette.
  bool load(const std::string& png_file_name) override;

  // Set the colour (really a palette index) at the given position index.
  void set_colour(int x, int y, COLOUR_INDEX ch) override
  {
    m_data[index(x, y)] = ch;
  }

  COLOUR_INDEX get_colour(int x, int y) const override
  {
    return m_data[index(x, y)];
  }

  virtual bool is_transparent(int x, int y) const override
  {
    return get_colour(x, y) == TRANSPARENT;
  }

  // * clear *
  // Clear image to the given colour (palette index)
  void clear(COLOUR_INDEX c = 0) override;

  // * blit *
  // Blit this image to the given destination image, at the given (x, y)
  //  coord in the destination.
  // Pixels with colour index TRANSPARENT are not copied.
  void blit(ref_image dest, int dest_x, int dest_y) const override;
	
  // * blit_region *
  // Blit a rectangular region of this source image to the destination.
  // Pixels with colour index TRANSPARENT are not copied.
  void blit_region(ref_image dest, int dest_x, int dest_y, 
    int src_x, int src_y, int src_w, int src_h) const override;

  static palette& get_palette();

private:
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
  std::vector<uint8_t> m_data;

  static palette m_pal;
};

