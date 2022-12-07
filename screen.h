// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include "image.h"

// * screen *
// 2D array which represents a lo-res screen: drawn to the window.
class screen : public image
{
public:
  // Size of virtual screen in pretend pixels
  static const int WIDTH = 128; 
  static const int HEIGHT = 128; 

  // * draw_on_gl_thread *
  // Execute OpenGL calls to draw this image onto the current render
  //  target, using the given palette to convert colour indices to
  //  RGB colours.
  void draw_on_gl_thread(const palette& pal);
};

