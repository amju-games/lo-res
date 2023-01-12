// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <GLUT/GLUT.h> // Mac
#include "image_8.h"
#include "palette.h"
#include "render_image_opengl.h"

void render_image_opengl(ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();
  // Draw array as coloured blocks
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {   
      COLOUR_INDEX ch = im->get_colour(x, y);
      colour col = image_8::get_palette().get_colour(ch);
      glColor3ub(col.r, col.g, col.b);

      // Flip y: we want y=0 at the top of the screen, not the bottom
      int yf = h - y;
      glRectf(x, yf - 1, x + 1, yf);
    }   
  }
}

