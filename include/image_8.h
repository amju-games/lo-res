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
  // Load a png image.
  // Adds the colours found in the image to the given palette.
  // Stores the image as indices into the palette.
  bool load(const std::string& png_file_name) override;

  // Set the colour or palette index at the given position index.
  void set_colour(int x, int y, colour ch) override;

  colour get_colour(int x, int y) const override;

  void clear(colour c) override;

  static palette& get_palette();

protected:
  static palette m_pal;
};

