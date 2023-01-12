// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#include <algorithm>
#include <cassert>
#include <iostream>
#include "sprite_sheet.h"

pix_int_result pixel_intersect(
  const sprite_sheet& ss1, int cell1, int x1, int y1, 
  const sprite_sheet& ss2, int cell2, int x2, int y2)
{
  // Cell sizes for both sprites 
  int w1 = ss1.get_cell_w();
  int h1 = ss1.get_cell_h();
  int w2 = ss2.get_cell_w();
  int h2 = ss2.get_cell_h();

#ifdef PIX_DEBUG
std::cout 
  << "Sprite 1: cell w: "  << w1 << " h: " << h1 
  << " Sprite 2: cell w: " << w2 << " h: " << h2 << "\n";
#endif

  // Overlapping range of coords
  int xmin = std::max(x1, x2);
  int xmax = std::min(x1 + w1, x2 + w2);
  int ymin = std::max(y1, y2);
  int ymax = std::min(y1 + h1, y2 + h2);

#ifdef PIX_DEBUG
std::cout
  << "Overlap: xmin: " << xmin << " xmax: " << xmax
  << " ymin: " << ymin << " ymax: " << ymax << "\n";
#endif

  // Bail if no overlapping region
  if (xmin >= xmax || ymin >= ymax)
  {
#ifdef PIX_DEBUG
std::cout << "NO OVERLAP\n";
#endif
    return pix_int_result::NO_AND_DISJOINT;
  }

  // Find region on both sprite sheets
  // Find top-left of cell for each sprite
  int cell_x1 = cell1 % ss1.m_cells_x * w1;
  int cell_y1 = cell1 / ss1.m_cells_x * h1;
  int cell_x2 = cell2 % ss2.m_cells_x * w2;
  int cell_y2 = cell2 / ss2.m_cells_x * h2;

#ifdef PIX_DEBUG
std::cout << "Top left cell coord: "
  << "cell_x1: " << cell_x1 << " cell_y1: " << cell_y1 
  << " cell_x2: " << cell_x2 << " cell_y2: " << cell_y2 << "\n";
#endif

  const p_image& image1 = ss1.get_image();
  const p_image& image2 = ss2.get_image();

  // Check corresponding pixels for non-transparent colour index
  int nx = xmax - xmin;
  int ny = ymax - ymin;
  for (int x = 0; x <nx; x++)
  {
    for (int y = 0; y < ny; y++) // better to swap for cache?
    {
      int px1 = cell_x1 + x + xmin - x1;
      int py1 = cell_y1 + y + ymin - y1;
      int px2 = cell_x2 + x + xmin - x2;
      int py2 = cell_y2 + y + ymin - y2;

#ifdef PIX_DEBUG
std::cout << "Testing pixel pairs: "
  << "(" << px1 << ", " << py1 << ") and "
  << "(" << px2 << ", " << py2 << ")\n";
#endif

      bool tr1 = image1->is_transparent(px1, py1);
      bool tr2 = image2->is_transparent(px2, py2);

      if (!tr1 && !tr2)
      {
#ifdef PIX_DEBUG
std::cout << "Both non-transparent, HIT!\n";
#endif
        return pix_int_result::YES_COLLIDE;
      } 
    }
  }
#ifdef PIX_DEBUG
std::cout << "No overlapping opaque pixels.\n";
#endif
  return pix_int_result::NO_AND_NOT_DISJOINT;
}

void sprite_sheet::draw_cell(ref_image dest, int cell, int dest_x, int dest_y) const
{
  // Draw cell at pos on screen
  // Calc cell x, y, w, h

  // Get top left of current cell (m_cell)
  assert(cell < m_cells_x * m_cells_y);
  int cell_x = cell % m_cells_x * m_cell_w;
  int cell_y = cell / m_cells_x * m_cell_h;

  m_image->blit_region(dest, dest_x, dest_y,
    cell_x, cell_y, m_cell_w, m_cell_h);
}

