// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <vector>
#include "image_decorator.h"
#include "uv.h"

// Filter is a vector of (offset, weight) pairs. 
// To perform filtering, we apply the filter to every source pixel.

using offset_weight = std::pair<uv, float>;
using filter = std::vector<offset_weight>;

class image_filter : public image_decorator
{
public:
  image_filter() = default;
  image_filter(p_image child, const filter& filter_ = {}) : image_decorator(child), m_filter(filter_) {}

  // Get mean of all filter elements applied to (x, y) on child image
  colour get_colour(int x, int y) const;

protected:
  filter m_filter;
};

