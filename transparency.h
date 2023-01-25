// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

// Useful transparency test to use as IS_TRANSPARENT type in mask/blend operations
//  for blitting

struct zero_alpha
{
  bool operator()(const colour& c)
  {
    return c.a == 0;
  }
};

