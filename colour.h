// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

// * colour *
// Struct representing (r, g, b) colour, 8 bits per channel.
struct colour
{
  colour() = default;
  colour(unsigned char r_, unsigned char g_, unsigned char b_) : 
    r(r_), g(g_), b(b_) {}

  bool operator==(const colour& c) const
  {
    return r == c.r && g == c.g && b == c.b;
  }

  unsigned char r = 0, g = 0, b = 0;
};

