// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

// clang++ *.cpp ../*.cpp -I.. -framework GLUT -framework OpenGL 
//   -std=c++11 -Wno-deprecated-declarations -DMACOSX

#include <array>
#include <cassert>
#include <iostream>
#include <GLUT/glut.h>
#include "blit.h"
#include "colour.h"
#include "font.h"
#include "image_8.h"
#include "image_32.h"
#include "image_filter.h"
#include "image_scale.h"
#include "image_uv_xform.h"
#include "palette.h"
#include "render_image_opengl.h"
#include "sprite.h"

// Size of window in actual device pixels
const int WINDOW_W = 500;
const int WINDOW_H = 500;

// Size in virtual pixels of pretent lo-res screen
const int VIRTUAL_W = 256;
const int VIRTUAL_H = 256;

const colour CLEAR_COLOUR = colour(0xff, 0xc0, 0);

using IMAGE_T = image_32;

p_image arrow1;
p_image arrow2;
sprite spr;
font my_font;

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  static p_image the_screen;
  if (!the_screen)
  {
    the_screen = std::make_shared<IMAGE_T>();
    the_screen->set_size(VIRTUAL_W, VIRTUAL_H);
  }

  the_screen->clear(CLEAR_COLOUR); 

  blit(arrow2, the_screen, 1, 64);
  my_font.draw(the_screen, 1, 130, "BLUR THEN SCALE");

  spr.draw(the_screen, 80, 64);
  my_font.draw(the_screen, 80, 130, "SCALE THEN BLUR");


  my_font.draw(the_screen, 5, 5, "HELLO\n1234567890!@^&*()_+-=<>,.?/\"':;");

  // Draw screen array to actual GL surface
  render_image_32_opengl(the_screen);

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

  image_8::get_palette().add_colour(colour(0, 0, 0));
  image_8::get_palette().add_colour(CLEAR_COLOUR);

  auto blur_filter = std::vector<std::pair<uv, float>>{
      {{0, 0}, 1},
      {{1, 0}, 1}, 
      {{0, 1}, 1}, 
      {{1, 1}, 1}
    };

  arrow1 = std::make_shared<IMAGE_T>();
  arrow1->load("assets/fruit_salad_32.png"); //arrow-in-box.png");

  // Make a sprite, apply scale then blur
  const float SCALE = 2.f;
  auto scale_dec = make_scale_xform(SCALE);
  scale_dec->set_child(arrow1);
  p_image blur_dec = std::make_shared<image_filter>(scale_dec, blur_filter);
  spr.set_image(blur_dec);
  spr.set_num_cells(1, 1);

  // Make another image, this time blur then scale
  auto scale_dec_2 = make_scale_xform(SCALE);
  p_image blur_dec_2 = std::make_shared<image_filter>(arrow1, blur_filter);
  scale_dec_2->set_child(blur_dec_2);
  arrow2 = scale_dec_2;

  // Load a font
  p_image im2 = std::make_shared<IMAGE_T>();
  im2->load("assets/font_4x4.png");
  my_font.set_image(im2); //std::make_shared<image_scale>(im2, 2.f));
  my_font.set_num_cells(16, 4);
  glutMainLoop();
}


