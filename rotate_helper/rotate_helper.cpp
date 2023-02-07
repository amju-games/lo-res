#include <cstdlib>
#include <cmath>
#include <iostream>
#include "blit.h"
#include "image_32.h"
#include "image_lighting.h"
#include "image_normal_map.h"
#include "image_uv_xform.h"
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
  std::string mult_filename;
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
    else if (str == "-m")
    {
      arg++;
      mult_filename = argv[arg];
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

  auto mult_image = std::make_shared<image_32>();
  if (!mult_filename.empty())
  {
    if (!mult_image->load(mult_filename))
    {
      std::cout << "Failed to load multiplier image \"" << mult_filename << "\"\n";
      return 1;
    }
  }

  normal_map_image = std::make_shared<image_32>();
  if (!normal_map_image->load(normal_map_filename))
  {
    std::cout << "Failed to load normal map image \"" << normal_map_filename << "\"\n";
    return 1;
  }
  normal_map = std::make_shared<image_normal_map>(normal_map_image);

  auto rotating_normal_map = std::make_shared<image_uv_xform>(normal_map);

  auto lighting = std::make_shared<image_lighting>(rotating_normal_map);
  lighting->set_specular_power(200.f);
  lighting->set_diffuse_colour(f_colour(.3f, .3f, 1.f).to_colour());

  auto rotating_mult_image = std::make_shared<image_uv_xform>(mult_image);

//  auto composite_image = std::make_shared

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
    
      alg3::vec2 centre_of_rot((cell_w - 1) / 2.f, (cell_h - 1) / 2.f);
      alg3::mat3 m = rotation2D(centre_of_rot, -degs);
      rotating_mult_image->set_xform(m); 
      rotating_normal_map->set_xform(m); 
      
      normal_map->set_rotation(alg3::rotation2D(alg3::vec2(0, 0), degs));

      degs += degs_per_frame;

      //blit<overwrite>(rotating_normal_map, out_image, x, y);
      blit<overwrite>(lighting, out_image, x, y);

      blit<overwrite>(rotating_mult_image, out_image, x, y);
    }
  }

  auto data = dynamic_cast<image_32*>(out_image.get())->get_data();
  lodepng_encode32_file("output.png", data, out_w, out_h); 

  return 0;
}


