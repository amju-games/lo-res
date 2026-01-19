// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image_n.h"

// * image_32 *
// Stores image as array of 32-bit RGBA values.

class image_32 : public image_n<4>
{
public:
  image_32() = default;

  image_32(int w, int h) : image_n(w, h) {}

  // * load *
  // Load a png image.
  bool load(const std::string& png_file_name) override;

  // * save *
  // Save a png image.
  // png_file_name: file path/name, should end with ".png".
  // Not an override, this is an image_32-only function.
  bool save(const std::string& png_file_name);

  colour get_colour(int x, int y) const override;

  void set_colour(int x, int y, colour ch) override;

  void clear(colour c) override;

  const uint8_t* get_data() const { return m_data.data(); }
};

