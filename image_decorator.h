// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image.h"

// * image decorator*
// Base class for decorators

class image_decorator : public image
{
public:
  image_decorator() = default;
  image_decorator(p_image child) : m_child(child) {}
  void set_child(p_image child) { m_child = child; }

  void set_size(int w, int h) override { m_child->set_size(w, h); }

  bool load(const std::string& png_file_name) override { return m_child->load(png_file_name); }

  void set_colour(int x, int y, colour ch) override { m_child->set_colour(x, y, ch); }

  colour get_colour(int x, int y) const override { return m_child->get_colour(x, y); }

  void clear(colour c) override { m_child->clear(c); }

  int get_width() const override { return m_child->get_width(); }
  int get_height() const override { return m_child->get_height(); }

protected:
  p_image m_child;
};

