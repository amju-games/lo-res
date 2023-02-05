#include <cstdlib>
#include <cmath>
#include <iostream>
#include "blit.h"
#include "image_32.h"
#include "image_lighting.h"
#include "image_normal_map.h"
#include "lodepng.h"

std::shared_ptr<image_32> normal_map_image;
std::shared_ptr<image_normal_map> normal_map;

float deg_to_rad(float r)
{
  return (r * 0.01745329252);
}

int main(int argc, char** argv)
{
  std::string normal_map_filename;
  int cells_in_x = 1;
  int cells_in_y = 1;

  int arg = 1;
  while (arg < argc)
  {
    std::string str = argv[arg];
    if (str == "-n")
    {
      arg++;
      normal_map_filename = argv[arg];
    }
    else if (str == "-cx")
    {
      arg++;
      cells_in_x = atoi(argv[arg]);
    }
    else if (str == "-cy")
    {
      arg++;
      cells_in_y = atoi(argv[arg]);
    }
    else
    {
      std::cout << "Unrecognised arg " << str << "\n";
      return 1;
    }

    arg++;
  }

  normal_map_image = std::make_shared<image_32>();
  if (!normal_map_image->load(normal_map_filename))
  {
    std::cout << "Failed to load normal map image \"" << normal_map_filename << "\"\n";
    return 1;
  }
  normal_map = std::make_shared<image_normal_map>(normal_map_image);

  auto lighting = std::make_shared<image_lighting>(normal_map);

  int cell_w = normal_map->get_width();
  int cell_h = normal_map->get_height();

  int num_cells = cells_in_x * cells_in_y;
  std::cout << "Num cells: " << num_cells << "\n";
  float degs_per_frame = 360.f / num_cells;

  std::shared_ptr<image> out_image = std::make_shared<image_32>();
  int out_w = cells_in_x * cell_w;
  int out_h = cells_in_y * cell_h;
  out_image->set_size(out_w, out_h);
  out_image->clear(colour(0xff, 0x80, 0));

  float degs = 0;  
  for (int i = 0; i < cells_in_y; i++)
  {
    for (int j = 0; j < cells_in_x; j++)
    {
      int x = j * cell_w;
      int y = i * cell_h;
      
      alg3::vec3 light_dir { cosf(deg_to_rad(degs)), sinf(deg_to_rad(degs)), 1.f };
      degs += degs_per_frame;
      lighting->set_light_dir(light_dir);

      blit<overwrite>(lighting, out_image, x, y);
    }
  }

  auto data = dynamic_cast<image_32*>(out_image.get())->get_data();
  lodepng_encode32_file("output.png", data, out_w, out_h); 

  return 0;
}


