// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

// clang++ *.cpp ../*.cpp -I.. -framework GLUT -framework OpenGL 
//   -std=c++11 -Wno-deprecated-declarations -DMACOSX

#include <array>
#include <cassert>
#include <iostream>
#include <GLUT/glut.h>
#include "colour.h"
#include "filler.h"
#include "font.h"
#include "image_8.h"
#include "image_32.h"
#include "palette.h"
#include "render_image_opengl.h"
#include "sprite.h"

// Size of window in actual device pixels
const int WINDOW_W = 800;
const int WINDOW_H = 600;

const int VIRTUAL_W = 128;
const int VIRTUAL_H = 96;

sprite spr;

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  static p_image the_screen;
  if (!the_screen)
  {
    the_screen = std::make_shared<image_32>();
    the_screen->set_size(VIRTUAL_W, VIRTUAL_H);
  }

  // Clear the screen
  fill(the_screen, solid_colour({0xff, 0xa0, 0}));

  // Draw the sprite 
  const int DEST_X = 2;
  const int DEST_Y = 2;
  spr.draw<mask_zero_alpha>(the_screen, DEST_X, DEST_Y);

  // Draw screen array to actual GL surface
  render_image_32_opengl(the_screen);

  glutSwapBuffers();
  glutPostRedisplay();
}

void update()
{
  const float dt = 0.0166f;

  spr.update(dt);
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
  std::string image_filename;
  int cells_in_x = 1;
  int cells_in_y = 1;
  float frame_time = 0.1f;

  if (argc == 1)
  {
    std::cout << "Animates cells on a sprite sheet.\n" 
      <<  argv[0] 
      << " -i <filename> -cx <cells in x> -cy <cells in y> -t <frame time seconds>\n"
      << "E.g.: " << argv[0] << " -i player_walk_1.png -cx 8 -cy 1 -t 0.15\n";
      return 1;
  }

  int arg = 1;
  while (arg < argc)
  {
    std::string str = argv[arg];
    if (str == "-i")
    {
      arg++;
      image_filename = argv[arg];
    }
    else if (str == "-cx")
    {
      arg++;
      cells_in_x = atoi(argv[arg]);
    }
    else if (str == "-cy")
    {
      arg++;
      cells_in_y = atoi(argv[arg]);
    }
    else if (str == "-t")
    {
      arg++;
      frame_time = atof(argv[arg]);
    }
    else
    {
      std::cout << "Unrecognised arg " << str << "\n";
      return 1;
    }

    arg++;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_W, WINDOW_H);
  glutCreateWindow("Hello");
  glutDisplayFunc(draw_and_update);

  image_8::get_palette().add_colour(colour(0, 0, 0));

  p_image im1 = std::make_shared<image_32>();
  im1->load(image_filename);

  sprite_sheet ss;
  ss.set_image(im1);
  ss.set_num_cells(cells_in_x, cells_in_y);

  spr.set_sprite_sheet(ss);
  spr.set_cell_time(frame_time);
  spr.set_cell_range(0, cells_in_x * cells_in_y - 1);

  glutMainLoop();
}


