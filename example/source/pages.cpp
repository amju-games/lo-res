// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include "blit.h"
#include "colour.h"
#include "double_buffer.h"
#include "draw_edge.h"
#include "draw_ellipse.h"
#include "draw_line.h"
#include "draw_point.h"
#include "filler.h"
#include "font.h"
#include "image_8.h"
#include "image_32.h"
#include "image_colour_transform.h"
#include "image_combine.h"
#include "image_filter.h"
#include "image_lighting.h"
#include "image_mask.h"
#include "image_normal_map.h"
#include "image_region.h"
#include "image_scale.h"
#include "image_sphere_map.h"
#include "image_uv_transform.h"
#include "make_sphere_normals.h"
#include "pages.h"
#include "palette.h"
#include "render_image_opengl.h"
#include "sprite.h"

// Size in virtual pixels of pretend lo-res screen
const int VIRTUAL_W = 128;
const int VIRTUAL_H = 128;

using IMAGE_T = image_32;

extern p_image the_screen;
extern font my_font;

#define do_once static int once = 1; if (once > 0 && once-- > 0)

static char last_key_down = 0;

#define do_on_key_down   char lkd = last_key_down; last_key_down = 0; if (lkd)


void apply_circular_mask(p_image im)
{
  // Create a circular image, apply to alpha channel of im
  int w = im->get_width();
  int h = im->get_height();
  p_image mask = std::make_shared<image_32>(w, h);
  fill(mask, solid_colour(colour(0, 0, 0, 0)));
  draw_ellipse_solid(mask, w / 2, h / 2, w / 2 - 2, h / 2 - 2, 
    colour(0xff, 0xff, 0xff, 0xff));
  auto masker = std::make_shared<image_mask<>>(im, mask);
  // Destructive, read from and write to image
  blit<overwrite>(masker, im, 0, 0);
}

void draw_edges(p_image im, int n)
{
  [[maybe_unused]] colour c[] = { 
    { 0xff, 0, 0 },
    { 0xff, 0xff, 0 },
    { 0xff, 0, 0xff },
    { 0, 0xff, 0 },
    { 0, 0xff, 0xff },
    { 0, 0, 0xff },
  };
 
  for (int i = 0; i < n; i++)
  {
    draw_edge(im, im, {0xff, 0xff, 0xff}, outline::outside);
  }
}

p_image create_cratered_normal_map(int w, int h, int num_craters)
{
  p_image gen_normal_map = std::make_shared<image_32>(w, h); 
  make_sphere_normals(gen_normal_map);

  // Blit some craters onto the normal map

  for (int i = num_craters; i > 0; i--) 
  {
    int r = 4 + i % (w / 4); //5; //rand() % (w / 3); 
    float crater_size = rand() % r;
    p_image crater = std::make_shared<image_32>(crater_size, crater_size);
 
    const bool convex = true;
    const bool concave = false;

    // First make a convex hemisphere. This will be the outer slope of the crater.
    make_sphere_normals(crater, convex); // first convex
    apply_circular_mask(crater);

    int x = rand() % w;
    int y = rand() % h;
    blit<mask_zero_alpha>(crater, gen_normal_map, x, y);    

    // Make inner concave part of the crater: same centre but slightly smaller 
    p_image crater_inner = std::make_shared<image_32>(crater_size - 1.5f, crater_size - 1.5f);
    make_sphere_normals(crater_inner, concave); // second inner concave map
    apply_circular_mask(crater_inner);
    blit<mask_zero_alpha>(crater_inner, gen_normal_map, x + 1, y + 1);    
  }

  // Mask the final normal map, as we will have drawn outside the
  //  initial circle.
  apply_circular_mask(gen_normal_map);
  return gen_normal_map;
}

p_image create_potato_normal_map(int w, int h, int minx, int maxx, int miny, int maxy)
{
  // w, h: size of dest
  // the bounding box is the size we need of the normal map within 
  //  the dest.
  // We give an extra 1-pixel border to make sure we cover 
  //  the whole potato.

  // +1 pixel extra on each side
  int w_nm = maxx - minx + 2;
  int h_nm = maxy - miny + 2;

  auto gen_normal_map = create_cratered_normal_map(w_nm, h_nm, 10);

  p_image dest = std::make_shared<image_32>(w, h);
  dest->clear({0xff, 0xff, 0}); // ?
  blit<overwrite>(gen_normal_map, dest, minx - 1, miny - 1);

  return dest;
}

void draw_white_potato(ref_image dest, int& minx, int& maxx, int& miny, int& maxy)
{
  // Draw white potato on transparent bg; keep track of bounding box.
  // Draw overlapping circles, following a short random curve
  //  for their centres.
  int w = dest->get_width();
  int h = dest->get_height();
  minx = w / 2;
  maxx = w / 2;
  miny = h / 2;
  maxy = h / 2;
  float scale = w / 64.f; // so a 64x64 potato is scale 1.0
  dest->clear({0, 0, 0, 0});

  // Start values
  int n = 3; // num points on a curve
  int x = 20 * scale;
  int y = 32.f * scale;
  float max_angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 4.f - 2.f;
  float dist = 4.f * scale;
  float dx = 1.f;
  float dy = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.f - .5f;
  float a = 0;
  int r = static_cast<int>(scale * 
    (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 4.f + 6.f));

  for (int i = 0; i < n; i++)
  {
    minx = std::min(minx, x - r);
    maxx = std::max(maxx, x + r);
    miny = std::min(miny, y - r);
    maxy = std::max(maxy, y + r);
    draw_ellipse_solid(dest, x, y, r, r, { 0xff, 0xff, 0xff });

    x += dx * dist + cos(a) * dist;
    y += dy * dist + sin(a) * dist;
    a += max_angle / n;
    r += (rand() % 3 - 1);
  }
}

void potato(ref_image dest)
{
  int w = dest->get_width();
  int h = dest->get_height();
  //float scale = w / 64.f;

  const float SCALE_UP = 1.f;
  p_image big_dest = std::make_shared<image_32>(w * SCALE_UP, h * SCALE_UP);

  int minx = 0, maxx = 0, miny = 0, maxy = 0;
  draw_white_potato(big_dest, minx, maxx, miny, maxy);

  // TODO Come back to this. 
  //auto rotated_pot = make_rotate_transform(big_dest, 0); //rand() % 360);

  // Draw an outer edge around the potato to smooth it off 
  //draw_edges(big_dest, 1);

  // Create normal map
  p_image normal_map = create_potato_normal_map(big_dest->get_width(), big_dest->get_height(), minx, maxx, miny, maxy);

//  auto scaled_pot = std::make_shared<image_scale>(big_dest, 1.f / SCALE_UP);

  // Use white potato as mask
  auto masker = std::make_shared<image_mask<>>(normal_map, big_dest);
  // Destructive, read from and write to image
  blit<overwrite>(masker, big_dest, 0, 0);

  blit<overwrite>(big_dest, dest, 0, 0); 
  //blit<overwrite>(normal_map, dest, 0, 0); 
}

std::vector<page> pages = 
{
page([]()
{
  // Trying out what Mame does for the galaxian starfield
  static constexpr int STAR_RNG_PERIOD = ((1 << 17) - 1);
  static std::vector<uint8_t> stars(STAR_RNG_PERIOD);
  static int star_rng_origin = 0x7563; //STAR_RNG_PERIOD - (m_screen->vpos() * 512 + m_screen->hpos());
  static int star_rng_origin_frame = 0; //m_screen->frame_number();

  do_once
  {
    int shiftreg = 0;
    for (int i = 0; i < STAR_RNG_PERIOD; i++)
    {
      /* stars are enabled if the upper 8 bits are 1 and the low bit is 0 */
      int enabled = ((shiftreg & 0x1fe01) == 0x1fe00); //originally: 0x1fe00);

      /* color comes from the 6 bits below the top 8 bits */
      int color = (~shiftreg & 0x1f8) >> 3;

      /* store the color value in the low 6 bits and the enable in the upper bit */
      stars[i] = color | (enabled << 7);

      /* the LFSR is fed based on the XOR of bit 12 and the inverse of bit 0 */
      shiftreg = (shiftreg >> 1) | ((((shiftreg >> 12) ^ ~shiftreg) & 1) << 16);
    }
  }

  static int frame = 0;
  frame++;
  int curframe = frame;
  if (curframe != star_rng_origin_frame)
  {
    int per_frame_delta = -1;//m_flipscreen_x ? 1 : -1;
    int total_delta = per_frame_delta * (curframe - star_rng_origin_frame);

    /* we can't just use % here because mod of a negative number is undefined */
    while (total_delta < 0)
    {
      total_delta += STAR_RNG_PERIOD;
    }

    /* now that everything is positive, do the mod */
    star_rng_origin = (star_rng_origin + total_delta) % STAR_RNG_PERIOD;
    star_rng_origin_frame = curframe;
  }

  // Draw stars
  for (int y = 0; y < 128; y++)
  {
    uint32_t star_offs = star_rng_origin + y * 512;
    //stars_draw_row(bitmap, maxx, y, star_offs, 0xff);
    for (int x = 0; x < 128; x++)
    {
      int enable_star = (y ^ (x >> 3)) & 1;
      uint8_t star = stars[star_offs++];

      if (star_offs >= STAR_RNG_PERIOD)
        star_offs = 0;

      if (enable_star && (star & 0x80) != 0) // && (star & 0xff) != 0)
      {
        //bitmap.pix(y, m_x_scale*x + 0) = m_star_color[star & 0x3f];
        //void draw_point(ref_image dest, int x, int y, const colour& c);

        draw_point(the_screen, x, y, colour(0xff, 0xff, 0)); 
      }
    }
  }


  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "STARFIELD");
}),

page([]()
{
  static p_image red, green, blue;
  static constexpr int radius = 50;

  do_once
  {
    red = std::make_shared<image_32>(radius * 2, radius * 2);
    red->clear(colour(0, 0, 0, 0));
    draw_ellipse_solid(red, radius, radius, radius -2, radius - 2, 
      colour(0xff, 0x00, 0x00));

    green = std::make_shared<image_32>(radius * 2, radius * 2);
    green->clear(colour(0, 0, 0, 0));
    draw_ellipse_solid(green, radius, radius, radius -2, radius - 2, 
      colour(0x00, 0xff, 0x00));

    blue = std::make_shared<image_32>(radius * 2, radius * 2);
    blue->clear(colour(0, 0, 0, 0));
    draw_ellipse_solid(blue, radius, radius, radius -2, radius - 2, 
      colour(0x00, 0x00, 0xff));
  }

  the_screen->clear({0, 0, 0});
  blit<add_blend>(red, the_screen, 64 - radius, 42 - radius);
  blit<add_blend>(green, the_screen, 42 - radius, 86 - radius);
  blit<add_blend>(blue, the_screen, 86 - radius, 86 - radius);

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "ADD TEST");
}),

page([]()
{
  static p_image red, green, blue;
  static constexpr int radius = 50;

  do_once
  {
    red = std::make_shared<image_32>(radius * 2, radius * 2);
    red->clear(colour(0, 0, 0, 0));
    draw_ellipse_solid(red, radius, radius, radius -2, radius - 2, 
      colour(0xff, 0x00, 0x00));

    green = std::make_shared<image_32>(radius * 2, radius * 2);
    green->clear(colour(0, 0, 0, 0));
    draw_ellipse_solid(green, radius, radius, radius -2, radius - 2, 
      colour(0x00, 0xff, 0x00));

    blue = std::make_shared<image_32>(radius * 2, radius * 2);
    blue->clear(colour(0, 0, 0, 0));
    draw_ellipse_solid(blue, radius, radius, radius -2, radius - 2, 
      colour(0x00, 0x00, 0xff));
  }

  the_screen->clear({0xff, 0xff, 0xff});
  blit<sub_blend>(red, the_screen, 64 - radius, 42 - radius);
  blit<sub_blend>(green, the_screen, 42 - radius, 86 - radius);
  blit<sub_blend>(blue, the_screen, 86 - radius, 86 - radius);

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "SUBTRACT TEST");
}),

page([]()
{
  static constexpr int size = 64;
  static p_image gen_normal_map = create_cratered_normal_map(size, size, 1);
  static std::shared_ptr<image_lighting> moon;

  do_once
  {
      moon = std::make_shared<image_lighting>(gen_normal_map);
      moon->set_light_dir({1.f, 1.f, 2.f}); 
      moon->set_ambient_colour({0x10, 0x10, 0x10 });
      moon->set_diffuse_colour({0x80, 0x80, 0x80 });
      moon->set_specular_power(100.f);
  }
  
  static int n = 100;

  do_on_key_down
  {
    n += 10;
    srand(0); 
    gen_normal_map = create_cratered_normal_map(size, size, n);
    moon->set_child(gen_normal_map); // TODO just modify normal map in-place
  }

  blit<mask_zero_alpha>(gen_normal_map, the_screen, 0, 10);
  blit<mask_zero_alpha>(moon, the_screen, 64, 10);

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "MOON");
}),

page([]()
{
  static std::vector<p_image> pots;
  do_once
  {
    for (int i = 0; i < 4; i++)
    {
      p_image im = std::make_shared<image_32>(32, 32);
      potato(im);
      pots.push_back(im);
    }
  }

  for (int i = 0; i < 4; i++)
  {
    blit<overwrite>(pots[i], the_screen, i * 32, 32);
  }
  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "POTATO");
}),

page([]()
{
  static p_image fruit = std::make_shared<image_32>();
  static p_image mask = std::make_shared<image_32>(128, 128);

  do_once
  {
    fruit->load("assets/fruit_salad_128.png");
    fill(mask, solid_colour(colour(0, 0, 0, 0)));
    draw_ellipse_solid(mask, 64, 64, 60, 60, colour(0xff, 0xff, 0xff, 0xff));
    draw_ellipse_solid(mask, 64, 64, 45, 45, colour(0xff, 0xff, 0xff, 0x00));
    draw_ellipse_solid(mask, 64, 64, 30, 30, colour(0xff, 0xff, 0xff, 0xff));
    draw_ellipse_solid(mask, 64, 64, 15, 15, colour(0xff, 0xff, 0xff, 0x80));
    
    auto masker = std::make_shared<image_mask<>>(fruit, mask);
    // Destructive, read from and write to image
    blit<overwrite>(masker, fruit, 0, 0);
  }

  blit<overwrite>(fruit, the_screen, 0, 0);
  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "MASK");
}),

page([]()
{
  static p_image noise_image_greyscale = std::make_shared<image_32>(64, 64);
  static p_image noise_image_colour = std::make_shared<image_32>(64, 64);
  do_once
  {
    fill(noise_image_greyscale, noise_greyscale());
    fill(noise_image_colour, noise_colour());
  }
  blit<overwrite>(noise_image_greyscale, the_screen, 0, 10);
  blit<overwrite>(noise_image_colour, the_screen, 64, 10);

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "NOISE");
}),

page([]()
{
  static constexpr int size = 32;

  static double_buffer fire_db(
     std::make_shared<image_32>(size, size),
     std::make_shared<image_32>(size, size));

  static auto bottom = std::make_shared<image_region>();
  static auto fire_filter = std::vector<std::pair<uv, float>>{
    {{-1, 0}, 1},              {{1, 0}, 1},
    {{-1, 1}, 1}, {{0, 1}, 1}, {{1, 1}, 1},
    {{-1, 2}, 1}, {{0, 2}, 1}, {{1, 2}, 1}
  };
  static auto filter = std::make_shared<image_filter>(fire_filter);

  do_once
  {
    fire_db.back()->clear({0, 0, 0});
    bottom->set_region(size / 4, size - 1, size / 2, 1);
  }

  bottom->set_child(fire_db.back());
  fill(bottom, noise_greyscale());
  filter->set_child(fire_db.back());
  blit<overwrite>(filter, fire_db.front(), 0, 0);
  blit<overwrite>(fire_db.front(), the_screen, 0, 10);
  fire_db.flip();

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "FIRE");
}),

page([]()
{
  static p_image src = std::make_shared<image_32>();
  static p_image dest = std::make_shared<image_32>();
  do_once
  {
    //src->load("assets/arrow-in-box.png");
    // TODO TEMP TEST
    src->load("../../jammy/village/assets/rotating_rock_0.png");
    dest->set_size(src->get_width(), src->get_height());
    dest->clear({0xff, 0xff, 0});
    draw_edge(src, dest, {0, 0, 0xff}, outline::inside);
  }

  blit<overwrite>(src, the_screen, 0, 10);
  blit<overwrite>(dest, the_screen, 64, 10);

  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "DRAW EDGE");
}),

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
    
    sphere_map = std::make_shared<image_colour_transform>(
      std::make_shared<image_sphere_map>(gen_normal_map, sphere_map_region),
      f_colour(1, 1, 1, 0.99f));

    std::shared_ptr combiner = std::make_shared<image_combine>(
          calc_alpha_blend);
    combiner->add_child(light);
    combiner->add_child(sphere_map); 

    std::shared_ptr combiner2 = std::make_shared<image_combine>(
      combiner,
      bubble_img,
      calc_add_blend);

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
  // rotate
  static p_image arrow1;
  static std::shared_ptr<image_uv_transform> rotated_arrow;
  static p_image blur_dec;
  static sprite spr;

  do_once
  {
    arrow1 = std::make_shared<IMAGE_T>();
    arrow1->load("assets/arrow-in-box.png");
    //  arrow1->load("assets/fruit_salad_32.png");

    sprite_sheet ss;
    ss.set_image(arrow1);
    ss.set_num_cells(1, 1);

    spr.set_sprite_sheet(ss);

    // Rotated image
    rotated_arrow = std::make_shared<image_uv_transform>(); 
    rotated_arrow->set_child(arrow1);
  }

//  alg3::vec2 centre_of_rot((fruit->get_width() - 1) / 2.f, (fruit->get_height() - 1) / 2.f); 
  static float angle = 0.f;
  angle += 1.0f;
//  alg3::mat3 m = rotation2D(centre_of_rot, angle);
  rotated_arrow->set_transform(make_rot_around_centre_matrix(rotated_arrow, angle));

  blit<add_blend>(rotated_arrow, the_screen, 0, 16);
  my_font.draw<mask_zero_alpha>(the_screen, 0, 0, "ROTATE");
}),

page([]()
{
  // scale and blur test

  static p_image fruit;
  static p_image blur_then_scale_up;
  static p_image scale_up_then_blur;

  do_once
  {
    const auto blur_filter = std::vector<std::pair<uv, float>>{
      {{0, 0}, 1},
      {{1, 0}, 1}, 
      {{0, 1}, 1}, 
      {{1, 1}, 1}
    };

    fruit = std::make_shared<IMAGE_T>();
    fruit->load("assets/fruit_salad_64.png");

    const float SCALE_UP_X = 2.f;
    const float SCALE_UP_Y = 2.f;

    scale_up_then_blur = std::make_shared<image_filter>(
      std::make_shared<image_scale>(fruit, SCALE_UP_X, SCALE_UP_Y),
      blur_filter);

    blur_then_scale_up = std::make_shared<image_scale>(
      std::make_shared<image_filter>(fruit, blur_filter),
      SCALE_UP_X, SCALE_UP_Y);
  }

  blit<overwrite>(fruit, the_screen, 0, 0);
  my_font.draw<mask_zero_alpha>(the_screen, 0, 0, "ORIGINAL");

  blit<overwrite>(blur_then_scale_up, the_screen, 0, 64);
  my_font.draw<mask_zero_alpha>(the_screen, 0, 64, "BLUR THEN SCALE");

  blit<overwrite>(scale_up_then_blur, the_screen, 64, 64);
  my_font.draw<mask_zero_alpha>(the_screen, 64, 64, "SCALE THEN BLUR");
}),

page([]()
{
  // scale and blur test

  static p_image fruit;
  static p_image blur_then_scale_down;
  static p_image scale_down_then_blur;

  do_once
  {
    const auto blur_filter = std::vector<std::pair<uv, float>>{
      {{0, 0}, 1},
      {{1, 0}, 1}, 
      {{0, 1}, 1}, 
      {{1, 1}, 1}
    };

    fruit = std::make_shared<IMAGE_T>();
    fruit->load("assets/fruit_salad_64.png");

    const float SCALE_DOWN_X = .5f;
    const float SCALE_DOWN_Y = .5f;

    scale_down_then_blur = std::make_shared<image_filter>(
      std::make_shared<image_scale>(fruit, SCALE_DOWN_X, SCALE_DOWN_Y),
      blur_filter);

    blur_then_scale_down = std::make_shared<image_scale>(
      std::make_shared<image_filter>(fruit, blur_filter),
      SCALE_DOWN_X, SCALE_DOWN_Y);
  }

  blit<overwrite>(fruit, the_screen, 0, 0);
  my_font.draw<mask_zero_alpha>(the_screen, 0, 0, "ORIGINAL");

  blit<overwrite>(blur_then_scale_down, the_screen, 0, 72);
  my_font.draw<mask_zero_alpha>(the_screen, 0, 64, "BLUR THEN SCALE");

  blit<overwrite>(scale_down_then_blur, the_screen, 64, 72);
  my_font.draw<mask_zero_alpha>(the_screen, 64, 64, "SCALE THEN BLUR");
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
  static constexpr int n = 10; // number of 'mipmap levels'
  static const int max_size = 32;
  static std::array<p_image, n> generated_normal_map;
  static std::array<std::shared_ptr<image_lighting>, n> lighting_example;

  do_once
  {
    int size = max_size;
    for (int i = 0; i < n; i++)
    {
      generated_normal_map[i] = std::make_shared<image_32>(size, size);
      const bool convex = true;
      make_sphere_normals(generated_normal_map[i], convex);
  
      lighting_example[i] = std::make_shared<image_lighting>(generated_normal_map[i]);
      lighting_example[i]->set_light_dir({1.f, 1.f, 2.f}); 
      lighting_example[i]->set_diffuse_colour({0xff, 0, 0 });
      lighting_example[i]->set_specular_power(50.f);
      
      if (size > 8)
      {
        size /= 2;
      }
      else if (size > 1)
      {
        size -= 1;
      }
    }
  }
  my_font.draw<mask_zero_alpha>(the_screen, 1, 1, "GENERATED NORMAL MAP AND LIGHTING");
  int y = 10;
  for (int i = 0; i < n; i++)
  {
    int size = generated_normal_map[i]->get_height();
    blit<overwrite>(generated_normal_map[i], the_screen, 0, y);
    blit<mask_zero_alpha>(lighting_example[i], the_screen, size, y);
    y += size;
  }
}) 

};


