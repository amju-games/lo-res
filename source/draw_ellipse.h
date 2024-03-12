#pragma once

#include "image.h"

void draw_ellipse_outline(ref_image dest, int centre_x, int centre_y, int radius_x, int radius_y, const colour& c);

void draw_ellipse_solid(ref_image dest, int centre_x, int centre_y, int radius_x, int radius_y, const colour& c);

