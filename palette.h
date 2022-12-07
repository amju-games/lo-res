// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

#include <vector>
#include "colour.h"

class palette
{
public:
  palette();
  int add_colour(const colour& col);
  const colour& get_colour(int c) const;

private:
  std::vector<colour> m_colours;
};

