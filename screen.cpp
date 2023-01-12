// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <GLUT/GLUT.h> // Mac
#include "palette.h"
#include "screen.h"

int screen::WIDTH = 64; 
int screen::HEIGHT = 64;

void screen::draw_on_gl_thread(const palette& pal)
{
  // Draw array as coloured blocks
  for (int x = 0; x < m_width; x++)
  {
    for (int y = 0; y < m_height; y++)
    {   
      COLOUR_INDEX ch = get_colour(x, y);
      colour col = pal.get_colour(ch);
      glColor3ub(col.r, col.g, col.b);

      // Flip y: we want y=0 at the top of the screen, not the bottom
      int yf = m_height - y;
      glRectf(x, yf - 1, x + 1, yf);
    }   
  }
}

