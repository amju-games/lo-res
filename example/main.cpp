// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

// clang++ *.cpp ../*.cpp -I.. -framework GLUT -framework OpenGL 
//   -std=c++11 -Wno-deprecated-declarations -DMACOSX

#include <array>
#include <cassert>
#include <iostream>
#include <GLUT/glut.h>
#include "colour.h"
#include "font.h"
#include "image.h"
#include "palette.h"
#include "screen.h"
#include "sprite.h"

// Size of window in actual device pixels
const int WINDOW_W = 500;
const int WINDOW_H = 500;

screen the_screen;

//image im; // TEST
sprite spr;
font my_font;

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  the_screen.clear(0); // black
  //im.blit(the_screen, 2, 60, 0);
  spr.draw(the_screen, 2, 2);
  my_font.draw(the_screen, 5, 5, "HELLO\n1234567890!@^&*()_+-=<>,.?/\"':;");

  // Draw screen array to actual GL surface
  the_screen.draw_on_gl_thread(image::get_palette());

  glutSwapBuffers();
  glutPostRedisplay();
}

void update()
{
  spr.update(0);
}

// * draw_and_update *
// Called every frame.
void draw_and_update()
{
  draw();
  update();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_W, WINDOW_H);
  glutCreateWindow("Hello");
  glutDisplayFunc(draw_and_update);

  gluOrtho2D(0, screen::WIDTH, 0, screen::HEIGHT);

  the_screen.set_size(screen::WIDTH, screen::HEIGHT);
  the_screen.clear(0);

  image::get_palette().add_colour(colour(0, 0, 0));

  p_image im1 = std::make_shared<image>();
  im1->load("assets/test2.png");
  spr.set_image(im1);
  spr.set_num_cells(1, 1);

  p_image im2 = std::make_shared<image>();
  im2->load("assets/font1.png");
  my_font.set_image(im2);
  my_font.set_num_cells(16, 4);
  glutMainLoop();
}


