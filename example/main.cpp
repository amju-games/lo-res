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
#include "draw_ellipse.h"
#include "draw_line.h"
#include "filler.h"
#include "font.h"
#include "image_8.h"
#include "image_32.h"
#include "image_colour_xform.h"
#include "image_combine.h"
#include "image_filter.h"
#include "image_lighting.h"
#include "image_mask.h"
#include "image_normal_map.h"
#include "image_region.h"
#include "image_scale.h"
#include "image_sphere_map.h"
#include "image_uv_xform.h"
#include "make_sphere_normals.h"
#include "palette.h"
#include "render_image_opengl.h"
#include "sprite.h"

// Size of window in actual device pixels
const int WINDOW_W = 500;
const int WINDOW_H = 500;

// Size in virtual pixels of pretent lo-res screen
const int VIRTUAL_W = 128;
const int VIRTUAL_H = 128;

const colour CLEAR_COLOUR = colour(0xff, 0xc0, 0);

using IMAGE_T = image_32;

p_image the_screen;
font my_font;

class page
{
public:
  page(std::function<void()> draw_func) : m_draw_func(draw_func) {}
  void draw() { m_draw_func(); }

  std::function<void()> m_draw_func;
};

#define do_once static int once = 1; if (once-- > 0)

int page_num = 0;
std::vector<page> pages = 
{
page([]()
{
  draw_ellipse_outline(the_screen, 
    60, 60,
    20, 30,
    f_colour(.2f, .5f, 1, 1).to_colour());

  draw_ellipse_outline(the_screen, 
    100, 100,
    30, 20,
    f_colour(1, 1, 1, 1).to_colour());

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "ELLIPSE");
}),

page([]()
{
  static p_image fruit;
  static p_image bubble_img;
  static std::shared_ptr<image_scale> bubble;
  static p_image sphere_map;
  static std::shared_ptr<image_region> sphere_map_region;
  static float bub_size = 50;
  static std::shared_ptr<image_lighting> light;

  do_once
  {
    fruit = std::make_shared<image_32>();
    fruit->load("assets/fruit_salad_128.png");
 
    bubble_img = std::make_shared<image_32>();
    bubble_img->set_size(bub_size, bub_size);
    fill(bubble_img, solid_colour(colour(0, 0, 0, 0)));

    draw_ellipse_outline(bubble_img, 
      bub_size / 2.f, 
      bub_size / 2.f, 
      bub_size / 2.f - 2, 
      bub_size / 2.f - 2, 
      f_colour(1, 1, 1, .5).to_colour());

    p_image gen_normal_map = std::make_shared<image_32>();
    gen_normal_map->set_size(bub_size, bub_size);
    make_sphere_normals(gen_normal_map);

    p_image mask = std::make_shared<image_32>();
    mask->set_size(bub_size, bub_size);
    fill(mask, solid_colour(colour(0, 0, 0, 0)));
    draw_ellipse_solid(mask, 
      bub_size / 2.f, 
      bub_size / 2.f, 
      bub_size / 2.f - 2, 
      bub_size / 2.f - 2, 
      colour(0xff, 0xff, 0xff, 0xff));
    // Mask off outside circle
    auto masker = std::make_shared<image_mask<>>(gen_normal_map, mask);
    // Destructive, read from and write to generated_normal_map
    blit<overwrite>(masker, gen_normal_map, 0, 0);

    light = std::make_shared<image_lighting>(gen_normal_map);
    light->set_ambient_colour(f_colour(.4f, .4f, .6f, .4f).to_colour());
    light->set_diffuse_colour(f_colour(.2f, .2f, .4f, .5f).to_colour());
    light->set_specular_colour(f_colour(1, 1, 1, .99f).to_colour());
    light->set_specular_power(80.f);
    light->set_light_dir({1.f, 1.f, 2.f}); 

    sphere_map_region = std::make_shared<image_region>(fruit, 0, 0, bub_size, bub_size);
    
    sphere_map = std::make_shared<image_colour_xform>(
      std::make_shared<image_sphere_map>(gen_normal_map, sphere_map_region),
      f_colour(1, 1, 1, 0.99f));

    std::shared_ptr combiner = std::make_shared<image_combine>(
          calc_alpha_blend);
    combiner->add_child(light);
    combiner->add_child(sphere_map); 

    std::shared_ptr combiner2 = std::make_shared<image_combine>(
      combiner,
      bubble_img,
      calc_additive_blend);

    bubble = std::make_shared<image_scale>(combiner2);
  }

  int w = bubble->get_width();
  int h = bubble->get_height();
  static float x = 60;
  static float y = 10;
  static float dx = .4f;
  static float dy = .4f;
  static float wobble = 0;
  wobble += .1f;
  bubble->set_scale(
    .9f + .1f * cosf(wobble), 
    .9f + .1f * sinf(wobble)); 
  x += dx;
  y += dy;
  dy += .001f;
  if (x < 0) dx = -dx;
  if (y < 0) dy = -dy;
  if ((x + w) > VIRTUAL_W) dx = -dx;
  if ((y + h) > VIRTUAL_H) dy = -dy;

  float w2 = VIRTUAL_W / 2.f;
  float h2 = VIRTUAL_H / 2.f; 
  light->set_light_dir({(x - w2)/w2, (y - h2)/h2, 2.f}); 

  blit<overwrite>(fruit, the_screen, 0, 0);

  // sphere map is subregion of background, which moves with bubble
  sphere_map_region->set_region(x, y);

  blit<alpha_blend>(bubble, the_screen, x, y);

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "WATER BUBBLE");
}),

page([]()
{
  static p_image fruit;
  static p_image arrow1;
  static p_image arrow2;
  static std::shared_ptr<image_uv_xform> rotated_arrow;
  static p_image blur_dec;
  static sprite spr;

  do_once
  {
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
  }

  blit<mask_zero_alpha>(arrow2, the_screen, 1, 64);
  my_font.draw<mask_zero_alpha>(the_screen, 1, 130, "BLUR THEN SCALE");

  spr.update(0);
  spr.draw<overwrite>(the_screen, 80, 64);
  my_font.draw<mask_zero_alpha>(the_screen, 80, 130, "SCALE THEN BLUR");


  alg3::vec2 centre_of_rot((fruit->get_width() - 1) / 2.f, (fruit->get_height() - 1) / 2.f); 
  static float angle = 0.f;
  angle += 1.0f;
  alg3::mat3 m = rotation2D(centre_of_rot, angle);
  rotated_arrow->set_xform(m);

  blit<additive_blend>(rotated_arrow, the_screen, 1, 150);
  my_font.draw<mask_zero_alpha>(the_screen, 1, 170, "ROTATED");

  my_font.draw<mask_zero_alpha>(the_screen, 5, 5, "HELLO\n1234567890!@^&*()_+-=<>,.?/\"':;");
}),

page([]()
{
  static std::shared_ptr<image_sphere_map> sphere_map_example;
  static std::shared_ptr<image_normal_map> normal_map;
  static p_image normal_map_img; // loaded from file

  do_once
  {
    normal_map_img = std::make_shared<image_32>();
    normal_map_img->load("assets/sphere_normal_map_32.png");
    // Decorate image so we can rotate it
    normal_map = std::make_shared<image_normal_map>(normal_map_img);

    sphere_map_example = std::make_shared<image_sphere_map>();
    sphere_map_example->add_child(normal_map);
    p_image fruit_32 = std::make_shared<image_32>();
    fruit_32->load("assets/fruit_salad_64.png");
    sphere_map_example->add_child(fruit_32);
  }

  // Rotate normal map
  static float angle = 0.f;
  angle += 1.0f;
  normal_map->set_rotation(alg3::rotation2D(alg3::vec2(0, 0), angle));

  blit<mask_zero_alpha>(sphere_map_example, the_screen, 32, 0);
  blit<overwrite>(normal_map_img, the_screen, 0, 32);
}),

page([]() 
{
  static p_image generated_normal_map;
  static std::shared_ptr<image_lighting> lighting_example;
  do_once
  {
    generated_normal_map = std::make_shared<image_32>();
    generated_normal_map->set_size(32, 32);
    make_sphere_normals(generated_normal_map);
    p_image mask = std::make_shared<image_32>();
    mask->set_size(32, 32);
    fill(mask, solid_colour(colour(0, 0, 0, 0)));
    draw_ellipse_solid(mask, 16, 16, 14, 12, colour(0xff, 0xff, 0xff, 0xff));
    // Mask off outside circle
    auto masker = std::make_shared<image_mask<>>(generated_normal_map, mask);
    // Destructive, read from and write to generated_normal_map
    blit<overwrite>(masker, generated_normal_map, 0, 0);
  
    lighting_example = std::make_shared<image_lighting>(generated_normal_map);
    lighting_example->set_light_dir({1.f, 1.f, 2.f}); 
    lighting_example->set_diffuse_colour({0xff, 0, 0 });
    lighting_example->set_specular_power(50.f);

  }
  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "GENERATED NORMAL MAP AND LIGHTING");
  blit<overwrite>(generated_normal_map, the_screen, 0, 10);
  blit<mask_zero_alpha>(lighting_example, the_screen, 32, 10);
}) 

};

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
  page_num++;
  if (page_num == pages.size())
  {
    page_num = 0;
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

 
