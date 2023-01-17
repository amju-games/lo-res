// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

// * colour *
// Struct representing (r, g, b, a) colour, 8 bits per channel.
struct colour
{
  colour() = default;
  colour(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 0xff) : 
    r(r_), g(g_), b(b_), a(a_) {}

  bool operator==(const colour& c) const
  {
    return r == c.r && g == c.g && b == c.b && a == c.a;
  }

  uint8_t r = 0, g = 0, b = 0, a = 0xff;
};

