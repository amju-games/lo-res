#include "draw_edge.h"

void draw_edge(const_ref_image src, ref_image dest, const colour& edge_colour, outline in_or_out)
{
  bool inside = (in_or_out == outline::inside);
 
  // Scan across each row, add an edge pixel when colour changes.
  // Then scan down each column.

  const int w = src->get_width();
  const int h = src->get_height();

  for (int y = 0; y < h; y++)
  {
    const colour start_col = src->get_colour(0, y);
    bool is_inside = false; // assume edge of src is "outside" shape we want to outline
    for (int x = 1; x < w; x++)
    {
      const colour c = src->get_colour(x, y);
      
      if (is_inside && c == start_col)
      {
        int dx = inside ? -1 : 0;
        dest->set_colour(x + dx, y, edge_colour);
        is_inside = false;
      }
      else if (!is_inside && c != start_col)
      {
        int dx = inside ? 0 : -1;
        dest->set_colour(x + dx, y, edge_colour);
        is_inside = true;
      }
    }
  }

  for (int x = 0; x < w; x++)
  {
    const colour start_col = src->get_colour(x, 0);
    bool is_inside = false; // assume edge of src is "outside" shape we want to outline
    for (int y = 1; y < h; y++)
    {
      const colour c = src->get_colour(x, y);
      
      if (is_inside && c == start_col)
      {
        int dy = inside ? -1 : 0;
        dest->set_colour(x, y + dy, edge_colour);
        is_inside = false;
      }
      else if (!is_inside && c != start_col)
      {
        int dy = inside ? 0 : -1;
        dest->set_colour(x, y + dy, edge_colour);
        is_inside = true;
      }
    }
  }
}


