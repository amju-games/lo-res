// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

#include <functional>
#include <vector>

// Each page shows some lo res technique or feature.
class page
{
public:
  page(std::function<void()> draw_func) : m_draw_func(draw_func) {}
  void draw() { m_draw_func(); }

  std::function<void()> m_draw_func;
};

extern std::vector<page> pages;


