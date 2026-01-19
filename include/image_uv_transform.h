// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "algebra3.h"
#include "image_decorator.h"


class image_uv_transform : public image_decorator
{
public:
  image_uv_transform() = default;
  image_uv_transform(p_image child) 
  {
    m_child = child;
    set_transform(alg3::identity2D());
  }

  image_uv_transform(p_image child, const alg3::mat3& matrix_)
  {
    m_child = child;
    set_transform(matrix_);
  }

  void set_transform(const alg3::mat3& matrix_) 
  { 
    m_matrix = matrix_; 
    m_inverse = m_matrix.inverse();
  }

  colour get_colour(int u, int v) const override;

  // We should also transform the dimensions of the image, i.e. apply scale/rotation
  //  but not translation.
  int get_width() const override;
  int get_height() const override;

protected:
  alg3::mat3 m_matrix;
  alg3::mat3 m_inverse;
};

// Handy function to make rotate transformers
std::shared_ptr<image_uv_transform> make_rotate_transform(p_image im, float angle_degs);

// Make a matrix to rotate an image around its centre
alg3::mat3 make_rot_around_centre_matrix(const p_image im, float angle_degs);

