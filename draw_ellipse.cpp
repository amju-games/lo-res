#include "draw_ellipse.h"
#include "draw_line.h"

/*
https://stackoverflow.com/questions/10322341/simple-algorithm-for-drawing-filled-ellipse-in-c-c


int hh = height * height;
int ww = width * width;
int hhww = hh * ww;
int x0 = width;
int dx = 0;

// do the horizontal diameter
for (int x = -width; x <= width; x++)
    setpixel(origin_x + x, origin_y);

// now do both halves at the same time, away from the diameter
for (int y = 1; y <= height; y++)
{
    int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
    for ( ; x1 > 0; x1--)
        if (x1*x1*hh + y*y*ww <= hhww)
            break;
    dx = x0 - x1;  // current approximation of the slope
    x0 = x1;

    for (int x = -x0; x <= x0; x++)
    {
        setpixel(origin_x + x, origin_y - y);
        setpixel(origin_x + x, origin_y + y);
    }
}

*/

void draw_ellipse_outline(ref_image dest, int origin_x, int origin_y, int width, int height, const colour& c)
{
  int hh = height * height;
  int ww = width * width;
  int hhww = hh * ww;
  int x0 = width;
  int dx = 0;

  // do the horizontal diameter
//  for (int x = -width; x <= width; x++)
//    plot(dest, origin_x + x, origin_y, c);

  plot(dest, origin_x - width, origin_y, c);
  plot(dest, origin_x + width, origin_y, c);

  // now do both halves at the same time, away from the diameter
  for (int y = 1; y <= height; y++)
  {
    int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
    for ( ; x1 > 0; x1--)
        if (x1*x1*hh + y*y*ww <= hhww)
            break;
    dx = x0 - x1;  // current approximation of the slope

    if (x0 > x1 + 1)
    {
      x0 -= 1;
    }
    else
    {
      x1 += 1;
    }
    for (int x = -x0; x < -x1; x++)
    {
        plot(dest, origin_x + x, origin_y - y, c);
        plot(dest, origin_x + x, origin_y + y, c);
    }
    for (int x = x1; x < x0; x++)
    {
        plot(dest, origin_x + x, origin_y - y, c);
        plot(dest, origin_x + x, origin_y + y, c);
    }
/*
    plot(dest, origin_x - x0, origin_y - y, c);
    plot(dest, origin_x + x0, origin_y + y, c);
    plot(dest, origin_x - x0, origin_y + y, c);
    plot(dest, origin_x + x0, origin_y - y, c);
*/
    x0 = x1;
  }
}

void draw_ellipse_solid(ref_image dest, int origin_x, int origin_y, int width, int height, const colour& c)
{
  int hh = height * height;
  int ww = width * width;
  int hhww = hh * ww;
  int x0 = width;
  int dx = 0;

  // do the horizontal diameter
  for (int x = -width; x <= width; x++)
    plot(dest, origin_x + x, origin_y, c);

  // now do both halves at the same time, away from the diameter
  for (int y = 1; y <= height; y++)
  {
    int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
    for ( ; x1 > 0; x1--)
        if (x1*x1*hh + y*y*ww <= hhww)
            break;
    dx = x0 - x1;  // current approximation of the slope
    x0 = x1;

    for (int x = -x0; x <= x0; x++)
    {
        plot(dest, origin_x + x, origin_y - y, c);
        plot(dest, origin_x + x, origin_y + y, c);
    }
  }
}


