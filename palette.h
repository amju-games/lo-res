// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <vector>
#include "colour.h"
#include "colour_index.h"

class palette
{
public:
  palette();
  int add_colour(const colour& col);
  const colour& get_colour(COLOUR_INDEX c) const;

private:
  std::vector<colour> m_colours;
};

