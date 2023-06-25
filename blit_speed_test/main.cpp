// "LO RES" Game Prototype
// Blit speed test
// (c) Juliet Colman 2023

// clang++ *.cpp ../*.cpp -I.. -framework GLUT -framework OpenGL 
//   -std=c++11 -Wno-deprecated-declarations -DMACOSX

#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include "blit.h"
#include "filler.h"
#include "image_32.h"

struct timer
{
  timer(const std::string& name) : m_name(name)
  {
    m_start = std::chrono::high_resolution_clock::now();
  }

  ~timer()
  {
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - m_start);
    std::cout << m_name << ": " << duration.count() << " µs\n";
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
  std::string m_name;
};

using func = std::function<void()>;

void time_runs(const std::string& name, int num_times, func f)
{
  std::cout << name << " ";
  auto total = 0;
  for (int i = 0; i < num_times; i++)
  {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    //std::cout << "Run " << i << ": " << duration.count() << " µs\n";
    std::cout << ".";
    std::cout.flush();
    total += duration.count();
  }
  std::cout << " mean: " << total / num_times << " µs\n";
}


int main()
{
  std::cout << "Blit speed test\n";

  const int IMG_W = 1024;
  const int IMG_H = 1024;

  p_image dest = std::make_shared<image_32>();
  dest->set_size(IMG_W, IMG_H);
 
  p_image src = std::make_shared<image_32>();
  src->set_size(IMG_W, IMG_H);

  // Blit src to dest using different blenders and decorators, collect timings.

  time_runs("Blit overwrite", 10, [&]() { 
    blit<overwrite>(src, dest, 0, 0);
  });

  time_runs("Blit with alpha blend", 10, [&]() { 
    blit<alpha_blend>(src, dest, 0, 0);
  });
}

