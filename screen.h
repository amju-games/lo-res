// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include "image.h"

// Size of virtual screen in pretend pixels
const int W = 64; 
const int H = 64; 

// * screen *
// 2D array which represents a lo-res screen: drawn to the window.
class screen : public image
{
public:
  void draw_on_gl_thread(const palette& pal);
};

