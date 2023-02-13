#include <cmath>
#include "draw_line.h"

void plot(ref_image dest, int x, int y, const colour& c)
{
  if (x >= 0 && x < dest->get_width() && y >= 0 && y < dest->get_height())
  {
    dest->set_colour(x, y, c);
  }
}

// Bresenham's line algorithm
// https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
void draw_line(ref_image dest, int x1, int y1, int x2, int y2, const colour& col)
{
  const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if(steep)
  {
    std::swap(x1, y1);
    std::swap(x2, y2);
  }
 
  if(x1 > x2)
  {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
 
  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);
 
  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;
 
  const int maxX = (int)x2;
 
  for(int x=(int)x1; x<maxX; x++)
  {
    if(steep)
    {
        plot(dest, y, x, col);
    }
    else
    {
        plot(dest, x, y, col);
    }
 
    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }
  }
}

