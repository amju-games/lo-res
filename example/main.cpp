// "LO RES" Game Prototype
// (c) Jason Colman 2017

// clang++ *.cpp ../*.cpp -I.. -framework GLUT -framework OpenGL 
//   -std=c++11 -Wno-deprecated-declarations -DMACOSX

#include <array>
#include <cassert>
#include <iostream>
#include <GLUT/glut.h>
#include "colour.h"
#include "image.h"
#include "palette.h"
#include "screen.h"
#include "sprite.h"
#include "timer.h"

// Size of window in actual device pixels
const int WINDOW_W = 500;
const int WINDOW_H = 500;

screen the_screen;
palette the_palette;
timer the_timer;

//image im; // TEST
sprite spr;

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  the_screen.clear(0); // black
  //im.blit(the_screen, 2, 60, 0);
  spr.draw(the_screen);

  the_screen.draw_on_gl_thread(the_palette);

  glutSwapBuffers();
  glutPostRedisplay();
}

void update()
{
  the_timer.update();

  spr.update(the_timer.get_dt());
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

  gluOrtho2D(0, W, 0, H);

  the_screen.set_size(W, H);
  the_screen.clear(0);

  the_palette.add_colour(colour(0, 0, 0));

  spr.load("assets/test2.png", the_palette);
  spr.set_vel(vec2(64.f, 0));

  glutMainLoop();
}


