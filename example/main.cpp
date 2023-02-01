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
#include "image_lighting.h"
#include "image_normal_map.h"
#include "image_sphere_map.h"
#include "image_uv_xform.h"
#include "palette.h"
#include "render_image_opengl.h"
#include "sprite.h"

// Size of window in actual device pixels
const int WINDOW_W = 500;
const int WINDOW_H = 500;

// Size in virtual pixels of pretent lo-res screen
const int VIRTUAL_W = 64;
const int VIRTUAL_H = 64;

const colour CLEAR_COLOUR = colour(0xff, 0xc0, 0);

using IMAGE_T = image_32;

std::shared_ptr<image_lighting> lighting_example;
std::shared_ptr<image_sphere_map> sphere_map_example;
std::shared_ptr<image_normal_map> normal_map;

p_image fruit;
p_image arrow1;
p_image arrow2;
std::shared_ptr<image_uv_xform> rotated_arrow;
p_image blur_dec;
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

  static float angle = 0.f;
  angle += 1.0f;

/*
  blit<mask_zero_alpha>(arrow2, the_screen, 1, 64);
  my_font.draw<mask_zero_alpha>(the_screen, 1, 130, "BLUR THEN SCALE");

  spr.draw<overwrite>(the_screen, 80, 64);
  my_font.draw<mask_zero_alpha>(the_screen, 80, 130, "SCALE THEN BLUR");


  alg3::vec2 centre_of_rot((fruit->get_width() - 1) / 2.f, (fruit->get_height() - 1) / 2.f); 
  alg3::mat3 m = rotation2D(centre_of_rot, angle);
  rotated_arrow->set_xform(m);

  blit<additive_blend>(rotated_arrow, the_screen, 1, 150);
  my_font.draw<mask_zero_alpha>(the_screen, 1, 170, "ROTATED");


  my_font.draw<mask_zero_alpha>(the_screen, 5, 5, "HELLO\n1234567890!@^&*()_+-=<>,.?/\"':;");
*/

  // Rotate normal map
  normal_map->set_rotation(alg3::rotation2D(alg3::vec2(0, 0), angle));

  blit<mask_zero_alpha>(lighting_example, the_screen, 0, 0);
  blit<mask_zero_alpha>(sphere_map_example, the_screen, 32, 0);
  
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

  fruit = std::make_shared<IMAGE_T>();
  fruit->load("assets/fruit_salad_64.png");

  arrow1 = std::make_shared<IMAGE_T>();
  arrow1->load("assets/arrow-in-box.png");
//  arrow1->load("assets/fruit_salad_32.png");


  // Colour xform


  // Make a sprite, apply scale then blur
  const float SCALEX = 2.f;
  const float SCALEY = 4.f;
  auto scale_dec = make_scale_xform(SCALEX, SCALEY);
  scale_dec->set_child(fruit); //arrow1);
  blur_dec = std::make_shared<image_filter>(scale_dec, blur_filter);
  spr.set_image(blur_dec);
  spr.set_num_cells(1, 1);


  // Rotated image
  rotated_arrow = std::make_shared<image_uv_xform>(); 
  rotated_arrow->set_child(fruit);


  // Make another image, this time blur then scale
  auto scale_dec_2 = make_scale_xform(SCALEX, SCALEY);
  p_image blur_dec_2 = std::make_shared<image_filter>(fruit, blur_filter);
  scale_dec_2->set_child(blur_dec_2);
  arrow2 = scale_dec_2;

  // Load a font
  p_image im2 = std::make_shared<IMAGE_T>();
  im2->load("assets/font_4x4.png");
  my_font.set_image(im2); //std::make_shared<image_scale>(im2, 2.f));
  my_font.set_num_cells(16, 4);

  // Lighting example
  p_image normal_map_img = std::make_shared<image_32>();
  normal_map_img->load("assets/sphere_normal_map_32.png");
  // Decorate image so we can rotate it
  normal_map = std::make_shared<image_normal_map>(normal_map_img);

  lighting_example = std::make_shared<image_lighting>(normal_map);
  lighting_example->set_light_dir({1.f, 1.f, 2.f}); 

  sphere_map_example = std::make_shared<image_sphere_map>();
  sphere_map_example->add_child(normal_map);
  p_image fruit_32 = std::make_shared<image_32>();
  fruit_32->load("assets/fruit_salad_64.png");
  sphere_map_example->add_child(fruit_32);

  glutMainLoop();
}

 
