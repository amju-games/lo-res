// "LO RES" Game Prototype
// (c) Jason Colman 2017

#pragma once

class timer
{
public:
  // * update *
  // Call this once per frame
  void update();

  float get_dt() const;
  float get_elapsed() const;
};

