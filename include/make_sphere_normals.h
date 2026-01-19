#pragma once

#include "image.h"

// Draw a normal map to the dest image, creating a curved hemisphere.
void make_sphere_normals(ref_image dest_image, bool convex = true);

