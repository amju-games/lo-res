#pragma once

#ifdef LO_RES_USE_FRAMEBUFFER

#include <cstdint>
#include <linux/fb.h>
#include "image.h"

class framebuffer : public image
{
public:
  framebuffer();
  ~framebuffer();
 
  void set_pixel(int x, int y, uint16_t colour_rgb_565);

  // TODO Shouldn't be part of image interface!
  void set_size(int w, int h) override {}

  // * load *
  // Load a png image.
  // TODO Shouldn't be part of image interface!
  bool load(const std::string& png_file_name) override { return false; }

  // Set the colour or palette index at the given position index.
  void set_colour(int x, int y, colour ch) override; 

  colour get_colour(int x, int y) const override;

  // * clear *
  // Clear image to the given colour (palette index)
  void clear(colour c) override;

  int get_width() const override;
  int get_height() const override; 
 
private:
  int m_filedescriptor = -1; 
  uint8_t* m_pixels = nullptr; 
  fb_fix_screeninfo m_fixed_info;
  fb_var_screeninfo m_var_info;
};

#endif // LO_RES_USE_FRAMEBUFFER

