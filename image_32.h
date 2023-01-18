// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image_n.h"

// * image_32 *
// Stores image as array of 32-bit RGBA values.

class image_32 : public image_n<4>
{
public:
  // * load *
  // Load a png image.
  bool load(const std::string& png_file_name) override;

  bool is_transparent(int x, int y) const override;

  colour get_colour(int x, int y) const override;

  void set_colour(int x, int y, colour ch) override;

  void clear(colour c) override;

  const uint8_t* get_data() const { return m_data.data(); }
};

