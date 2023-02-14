#include <cmath>
#include "algebra3.h"
#include "make_sphere_normals.h"

void make_sphere_normals(ref_image im)
{
  int w = im->get_width();
  int h = im->get_height();
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      // u and v are in range -1 .. 1
      float u = static_cast<float>(x) / static_cast<float>(w) * 2.f - 1.f;
      float v = (1.f - static_cast<float>(y) / static_cast<float>(h)) * 2.f - 1.f;

      // Eq of sphere x^2 + y^2 + z^2 = r^2 = 1 here.
      // =>  z = sqrt(1 - x^2 - y^2)
      float z = sqrtf(1 - u * u - v * v);
      alg3::vec3 n(u, v, z);
      n.normalize(); // shouldn't make any difference to the circle, but masks the edges
      n *= 0.5f;
      n += alg3::vec3(.5f, .5f, .5f);  

      colour c2 = f_colour(n[0], n[1], n[2]).to_colour();

      im->set_colour(x, y, c2);
    }
  }
}

