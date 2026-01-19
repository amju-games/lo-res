// "LO RES" Game library
// (c) Juliet Colman 2023

#pragma once

#include "image.h"

// Wrap two images, flip between the 'front' and 'back' image. 
class double_buffer 
{
public:
  double_buffer() = default;

  double_buffer(p_image f, p_image b)
  {
    m_images[0] = f;
    m_images[1] = b;
  }

  void set_front(p_image front_image) { m_images[m_front] = front_image; }
  void set_back(p_image back_image) { m_images[1 - m_front] = back_image; }
 
  ref_image front() { return m_images[m_front]; }
  ref_image back() { return m_images[1 - m_front]; }

  void flip() { m_front = 1 - m_front; }
 
protected:
  std::array<p_image, 2> m_images;
  int m_front = 0;
};


