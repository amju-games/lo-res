// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#ifdef LO_RES_USE_OPENGL

#include "image.h"

void render_image_32_opengl(const_ref_image i);

// TODO render any image type, if image exposes data.
void render_image_8_opengl(const_ref_image i);

void render_image_8_opengl_multiple_rects(const_ref_image i);

#endif // LO_RES_USE_OPENGL
