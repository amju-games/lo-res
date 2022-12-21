// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "image.h"

// * screen *
// 2D array which represents a lo-res screen: drawn to the window.
class screen : public image
{
public:
  // Size of virtual screen in pretend pixels. 
  // Set this in game-specific main function, but then can conveniently 
  //  get the size here.
  static int WIDTH; 
  static int HEIGHT; 

  // * draw_on_gl_thread *
  // Execute OpenGL calls to draw this image onto the current render
  //  target, using the given palette to convert colour indices to
  //  RGB colours.
  void draw_on_gl_thread(const palette& pal);
};

