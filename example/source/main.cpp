// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

// clang++ *.cpp ../*.cpp -I.. -framework GLUT -framework OpenGL 
//   -std=c++11 -Wno-deprecated-declarations -DMACOSX

#ifdef LO_RES_USE_OPENGL

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

#ifdef MACOSX
#include <GLUT/glut.h>
#endif

#include "colour.h"
#include "font.h"
#include "image.h"
#include "image_8.h"
#include "image_32.h"
#include "pages.h"
#include "render_image_opengl.h"

// Size of window in actual device pixels
const int WINDOW_W = 500;
const int WINDOW_H = 500;

// Size in virtual pixels of pretent lo-res screen
const int VIRTUAL_W = 128;
const int VIRTUAL_H = 128;

const colour CLEAR_COLOUR = colour(0xff, 0xc0, 0);

p_image the_screen;
font my_font;

static char last_key_down = 0;
static void set_key_down(char c) { last_key_down = c; } 
#define do_on_key_down   char lkd = last_key_down; last_key_down = 0; if (lkd)

int page_num = 0;

void draw()
{
  the_screen->clear(CLEAR_COLOUR); 

  pages[page_num].draw();

  // Draw screen array to actual GL surface
  render_image_32_opengl(the_screen);

  glutSwapBuffers();
  glutPostRedisplay();
}

void key_down(unsigned char c, int, int)
{
  set_key_down(c);

  if (c == 'f' || c == 'F' || c == ' ')
  {
    page_num++;
    if (page_num == pages.size())
    {
      page_num = 0;
    }
  }
  else if (c == 'b' || c == 'B')
  {
    page_num--;
    if (page_num < 0)
    {
      page_num = pages.size() - 1;
    }
  }

  std::cout << "Going to page " << page_num << "\n";
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_W, WINDOW_H);
  glutCreateWindow("Hello");
  glutDisplayFunc(draw);
  glutKeyboardFunc(key_down);

  the_screen = std::make_shared<image_32>();
  the_screen->set_size(VIRTUAL_W, VIRTUAL_H);

  image_8::get_palette().add_colour(colour(0, 0, 0));
  image_8::get_palette().add_colour(CLEAR_COLOUR);

  // Load a font
  p_image im2 = std::make_shared<image_32>();
  im2->load("assets/font_3x5.png");
  my_font.set_image(im2); 
  my_font.set_num_cells(16, 4);

  glutMainLoop();
}

#endif // LO_RES_USE_OPENGL

