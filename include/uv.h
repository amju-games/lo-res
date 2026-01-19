// "LO RES" Game Prototype
// (c) Juliet Colman 2017-2022

#pragma once

struct uv
{
  uv() = default;
  uv(int u_, int v_) : u(u_), v(v_) {}

  int u = 0;
  int v = 0;
};

inline uv operator+(const uv& uv1, const uv& uv2)
{
  return uv(uv1.u + uv2.u, uv1.v + uv2.v);
}

