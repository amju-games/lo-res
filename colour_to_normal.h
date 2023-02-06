#pragma once

#include <algorithm>
#include "algebra3.h"
#include "colour.h"

inline alg3::vec3 colour_to_normal(const colour& c)
{
  return alg3::vec3(c.r / 128.f - 1.f, c.g / 128.f - 1.f, c.b / 128.f - 1.f); 
}

inline colour normal_to_colour(const alg3::vec3& n)
{
  return colour(
    static_cast<uint8_t>(std::clamp(static_cast<int>((n[0] + 1.f) * 128.f + .5f), 0, 0xff)),
    static_cast<uint8_t>(std::clamp(static_cast<int>((n[1] + 1.f) * 128.f + .5f), 0, 0xff)),
    static_cast<uint8_t>(std::clamp(static_cast<int>((n[2] + 1.f) * 128.f + .5f), 0, 0xff)));
}

