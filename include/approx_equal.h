#pragma once

// Functions to check equality with epsilon tolerance value.
// Intended for use in unit tests.

#include "algebra3.h"
#include "colour.h"

static constexpr float APPROX_EQUAL_DEFAULT_EPSILON = 0.0001f;

// Colours are represented as uint_8s
static constexpr int APPROX_EQUAL_DEFAULT_COLOUR_EPSILON = 1;

inline bool approx_equal(float f1, float f2, 
  float epsilon = APPROX_EQUAL_DEFAULT_EPSILON)
{
  return (fabs(f1 - f2) < epsilon);
}

inline bool approx_equal(int i1, int i2, float epsilon)
{
  return (abs(i1 - i2) < epsilon);
}

inline bool approx_equal(const alg3::vec3& v1, const alg3::vec3& v2, 
  float epsilon = APPROX_EQUAL_DEFAULT_EPSILON)
{
  return 
    (   approx_equal(v1[0], v2[0], epsilon)
     && approx_equal(v1[1], v2[1], epsilon)
     && approx_equal(v1[2], v2[2], epsilon));
}

inline bool approx_equal(const colour& c1, const colour& c2,
  int epsilon = APPROX_EQUAL_DEFAULT_COLOUR_EPSILON)
{
  return
    (   approx_equal(c1.r, c2.r, epsilon)
     && approx_equal(c1.g, c2.g, epsilon)
     && approx_equal(c1.b, c2.b, epsilon)
     && approx_equal(c1.a, c2.a, epsilon));
}



