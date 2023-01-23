// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <GLUT/GLUT.h> // Mac
#include "image_8.h"
#include "image_32.h"
#include "palette.h"
#include "render_image_opengl.h"

namespace
{
void copy_image_8_to_array(const_ref_image im, uint8_t* data)
{
  uint8_t* d = data;
  int w = im->get_width();
  int h = im->get_height();
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {   
      colour col = im->get_colour(x, y);
      *d++ = col.r;
      *d++ = col.g;
      *d++ = col.b;
      *d++ = 0xff;
    }   
  }
}

GLuint initialise_gl_texture(int w, int h, int format, uint8_t* data)
{
  GLuint tex_id;
  glGenTextures(1, &tex_id);
  glBindTexture(GL_TEXTURE_2D, tex_id);

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

  return tex_id;
}

void update_gl_texture(GLuint tex_id, int w, int h, int format, uint8_t* data)
{
  glBindTexture(GL_TEXTURE_2D, tex_id);

  glTexSubImage2D(
    GL_TEXTURE_2D,
    0,
    0, 0,
    w, h,
    format,
    GL_UNSIGNED_BYTE,
    data);
}

void draw_gl_textured_quad()
{
  glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, 0);
  glEnd();
}

void render_gl_rgba_data(int w, int h, uint8_t* data)
{
  glEnable(GL_TEXTURE_2D);
  static GLuint tex_id = -1; 
  const int format = GL_RGBA;

  [[maybe_unused]] static bool do_once = [&]()
  {
    tex_id = initialise_gl_texture(w, h, format, data);
    return true;
  }();

  update_gl_texture(tex_id, w, h, format, data);

  draw_gl_textured_quad();
}

} // namespace

void render_image_32_opengl(const_ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();
  uint8_t* data = const_cast<uint8_t*>(std::dynamic_pointer_cast<const image_32>(im)->get_data());
  render_gl_rgba_data(w, h, data);
}

void render_image_8_opengl(const_ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();

  static uint8_t* data = new uint8_t[w * h * 4];

  // Copy texels into data... TODO get data directly from image for image_32.
  // For image_8, can we use colour index mode?
  copy_image_8_to_array(im, data);

  render_gl_rgba_data(w, h, data);
}

void render_image_8_opengl_multiple_rects(const_ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();

  // Draw array as coloured rects
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {   
      colour col = im->get_colour(x, y);
      glColor3ub(col.r, col.g, col.b);

      // Flip y: we want y=0 at the top of the screen, not the bottom
      int yf = h - y;
      glRectf(x, yf - 1, x + 1, yf);
    }   
  }
}

