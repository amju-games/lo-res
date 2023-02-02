// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#ifdef UNIT_TEST
#ifndef COLOUR_DEBUG
#define COLOUR_DEBUG
#endif
#endif

#ifdef COLOUR_DEBUG
#include <iostream>
#endif

#include <algorithm>
#include <cstdint>

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


inline colour colour_from_floats(float r, float g, float b, float a = 1.f)
{
  return colour(
    static_cast<uint8_t>(r * 255.f), 
    static_cast<uint8_t>(g * 255.f), 
    static_cast<uint8_t>(b * 255.f), 
    static_cast<uint8_t>(a * 255.f));
}


#ifdef COLOUR_DEBUG
inline std::ostream& operator<<(std::ostream& os, const colour& c)
{
  return os 
    << "(" 
    << static_cast<int>(c.r) << ", " 
    << static_cast<int>(c.g) << ", "
    << static_cast<int>(c.b) << ", " 
    << static_cast<int>(c.a) << ")";
}
#endif


// High value colours: allows us to e.g. add colours without overflowing.

struct h_colour
{
  h_colour() = default;
  h_colour(int r_, int g_, int b_, int a_) : r(r_), g(g_), b(b_), a(a_) {}
  h_colour(const colour& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

  colour to_colour() const 
  { 
    return colour(
      static_cast<uint8_t>(std::clamp(r, 0, 0xff)),
      static_cast<uint8_t>(std::clamp(g, 0, 0xff)),
      static_cast<uint8_t>(std::clamp(b, 0, 0xff)),
      static_cast<uint8_t>(std::clamp(a, 0, 0xff)));
  }

  h_colour& operator+=(const h_colour& h)
  {
    r += h.r;
    g += h.g;
    b += h.b;
    a += h.a;
    return *this;
  }

  h_colour& operator*=(const h_colour& h)
  {
    r *= h.r;
    g *= h.g;
    b *= h.b;
    a *= h.a;
    return *this;
  }

  h_colour& operator*=(float f)
  {
    r = static_cast<int>(f * static_cast<float>(r));
    g = static_cast<int>(f * static_cast<float>(g));
    b = static_cast<int>(f * static_cast<float>(b));
    a = static_cast<int>(f * static_cast<float>(a));
    return *this;
  }

  int r = 0, g = 0, b = 0, a = 0xff;
};

inline h_colour operator+(const h_colour& h1, const h_colour& h2)
{
  h_colour h(h1);
  h += h2;
  return h;
}

inline h_colour operator*(const h_colour& h1, const h_colour& h2)
{
  h_colour h(h1);
  h *= h2;
  return h;
}

inline h_colour operator*(const h_colour& h1, float f)
{
  h_colour h(h1);
  h *= f;
  return h;
}

