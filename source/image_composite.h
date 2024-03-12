#pragma once

#include <vector>
#include "image.h"

class image_composite : public image
{
public:
  void set_size(int w, int h) override 
  { 
    m_children[m_active_child]->set_size(w, h); 
  }

  bool load(const std::string& png_file_name) override 
  { 
    return m_children[m_active_child]->load(png_file_name); 
  }

  void set_colour(int x, int y, colour c) override
  {
    m_children[m_active_child]->set_colour(x, y, c);
  }

  colour get_colour(int x, int y) const override
  {
    return m_children[m_active_child]->get_colour(x, y);
  }

  void clear(colour c) override
  {
    m_children[m_active_child]->clear(c);
  } 

  int get_width() const override
  {
    return m_children[m_active_child]->get_width();
  }

  int get_height() const override
  {
    return m_children[m_active_child]->get_height();
  }

  void add_child(p_image child) { m_children.push_back(child); }

  void set_active_child(int i) { m_active_child = i; }

protected:
  int m_active_child = 0;
  std::vector<p_image> m_children;
};


