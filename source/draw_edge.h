#pragma once

#include "image.h"

// * draw_edge *
// Detect edges in src, draw to dest.
// Inside: draw edge within the source shape; 
// Outside: draw edge around, giving extra thickness.
enum class outline { inside, outside };
void draw_edge(const_ref_image src, ref_image dest, const colour& edge_colour, outline in_or_out);

