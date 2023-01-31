#pragma once

#include "algebra3.h"
#include "colour.h"

inline alg3::vec3 colour_to_normal(const colour& c)
{
  return alg3::vec3(c.r / 128.f - 1.f, c.g / 128.f - 1.f, c.b / 128.f - 1.f); 
}

