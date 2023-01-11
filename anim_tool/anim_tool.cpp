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

sprite spr;

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  the_screen.clear(0); // black
  spr.draw(the_screen, 2, 2);

  // Draw screen array to actual GL surface
  the_screen.draw_on_gl_thread(image::get_palette());

  glutSwapBuffers();
  glutPostRedisplay();
}

void update()
{
  float dt = 0.0166f;

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

  gluOrtho2D(0, screen::WIDTH, 0, screen::HEIGHT);

  the_screen.set_size(screen::WIDTH, screen::HEIGHT);
  the_screen.clear(0);

  image::get_palette().add_colour(colour(0, 0, 0));

  p_image im1 = std::make_shared<image>();
  im1->load(image_filename);
  spr.set_image(im1);
  spr.set_num_cells(cells_in_x, cells_in_y);
  spr.set_cell_time(frame_time);
  spr.set_cell_range(0, cells_in_x * cells_in_y - 1);
  glutMainLoop();
}


