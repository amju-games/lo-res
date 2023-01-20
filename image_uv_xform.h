#pragma once

#include "algebra3.h"
#include "image_decorator.h"


class image_uv_xform : public image_decorator
{
public:
  image_uv_xform() = default;
  image_uv_xform(p_image child, const mat3& matrix_)
  {
    m_child = child;
    set_xform(matrix_);
  }

  void set_xform(const mat3& matrix_) 
  { 
    m_matrix = matrix_; 
    m_inverse = m_matrix.inverse();
  }

  colour get_colour(int u, int v) const override;

  // We should also xform the dimensions of the image, i.e. apply scale/rotation
  //  but not translation.
  int get_width() const override;
  int get_height() const override;

protected:
  mat3 m_matrix;
  mat3 m_inverse;
};


// Handy functions to make common xformers
std::shared_ptr<image_uv_xform> make_scale_xform(float uniform_scale);
std::shared_ptr<image_uv_xform> make_scale_xform(float scale_x, float scale_y);

std::shared_ptr<image_uv_xform> make_rotate_xform(float angle_degs);

