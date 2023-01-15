// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <memory>
#include <string>
#include "colour_index.h"
#include "uv.h"

// * image *

class image;

using p_image = std::shared_ptr<image>;

// It's safe to pass p_images around but more efficient to use ref_image when we don't
//  care about incrementing the ref count, and can be sure that the ref count won't hit
//  zero while we're doing stuff. 
using ref_image = p_image&;

using const_ref_image = const std::shared_ptr<const image>&;

class image
{
public:
  virtual ~image() = default;

  // * set_size *
  // As an alternative to loading an image from a file, set the size
  //  and set pixel colours.
  virtual void set_size(int w, int h) = 0;

  // * load *
  // Load a png image.
  virtual bool load(const std::string& png_file_name) = 0;

  // Set the colour or palette index at the given position index.
  virtual void set_colour(int x, int y, COLOUR_INDEX ch) = 0;

  virtual COLOUR_INDEX get_colour(int x, int y) const = 0;

  virtual bool is_transparent(int x, int y) const = 0;

  // * clear *
  // Clear image to the given colour (palette index)
  virtual void clear(COLOUR_INDEX c = 0) = 0;

  virtual int get_width() const = 0; 
  virtual int get_height() const = 0;
};

