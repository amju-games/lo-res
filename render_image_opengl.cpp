// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <GLUT/GLUT.h> // Mac
#include "image_8.h"
#include "palette.h"
#include "render_image_opengl.h"

namespace
{
void copy_image_8_to_array(ref_image im, uint8_t* data)
{
  uint8_t* d = data;
  int w = im->get_width();
  int h = im->get_height();
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {   
      COLOUR_INDEX ch = im->get_colour(x, y);
      colour col = image_8::get_palette().get_colour(ch);
      *d++ = col.r;
      *d++ = col.g;
      *d++ = col.b;
      *d++ = 0xff;
    }   
  }
}
} // namespace

void render_image_8_opengl(ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();

  static uint8_t* data = new uint8_t[w * h * 4];

  // Copy texels into data... TODO get data directly from image for image_32.
  // For image_8, can we use colour index mode?
  copy_image_8_to_array(im, data);

  glEnable(GL_TEXTURE_2D);
  static GLuint texId = -1; 
  const int format = GL_RGBA;

  [[maybe_unused]] static bool do_once = [&]()
  {
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexImage2D(GL_TEXTURE_2D,
      0,
      format,
      w,
      h,
      0,
      format,
      GL_UNSIGNED_BYTE,
      data);

    glTexParameterf(
      GL_TEXTURE_2D,
      GL_TEXTURE_MAG_FILTER,
      GL_NEAREST);
    glTexParameterf(
      GL_TEXTURE_2D,
      GL_TEXTURE_MIN_FILTER,
      GL_NEAREST);

    return true;
  }();

  glBindTexture(GL_TEXTURE_2D, texId);

  glTexSubImage2D(
    GL_TEXTURE_2D,
    0,
    0, 0,
    w, h,
    format,
    GL_UNSIGNED_BYTE,
    data);

  glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, 0);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, 0);
  glEnd();
}

void render_image_8_opengl_multiple_rects(ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();

  // Draw array as coloured rects
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {   
      COLOUR_INDEX ch = im->get_colour(x, y);
      colour col = image_8::get_palette().get_colour(ch);
      glColor3ub(col.r, col.g, col.b);

      // Flip y: we want y=0 at the top of the screen, not the bottom
      int yf = h - y;
      glRectf(x, yf - 1, x + 1, yf);
    }   
  }
}

