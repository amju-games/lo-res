// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include "sprite_sheet.h"

class font : public sprite_sheet
{
public:
  void draw(image& dest, int dest_x, int dest_y, const std::string& text);
};

