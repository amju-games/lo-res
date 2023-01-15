// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image_n.h"
#include "palette.h"

// * image_8 *
// Stores image as a rectangular array of 8-bit indices into a palette of
//  colours. 


class image_8 : public image_n<1>
{
public:
  // Pixels with this colour index are transparent, i.e. not copied in
  //  blit operations.
  static const COLOUR_INDEX TRANSPARENT; 

  // * load *
  // Load an RGB 24-bit png image.
  // Adds the colours found in the image to the given palette.
  // Stores the image as indices into the palette.
  bool load(const std::string& png_file_name) override;

  virtual bool is_transparent(int x, int y) const override
  {
    return get_colour(x, y) == TRANSPARENT;
  }

  static palette& get_palette();

protected:
  static palette m_pal;
};

