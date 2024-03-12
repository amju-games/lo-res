#include <cstdlib>
#include <cmath>
#include <iostream>
#include "blit.h"
#include "image_32.h"
#include "image_lighting.h"
#include "image_normal_map.h"
#include "image_uv_transform.h"
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
  int cell_w = 0;
  int cell_h = 0;
  std::shared_ptr<image_uv_transform> rotating_normal_map;
  std::shared_ptr<image_lighting> lighting;
  std::shared_ptr<image_uv_transform> rotating_mult_image;

  int arg = 1;
  while (arg < argc)
  {
    std::string str = argv[arg];
    if (str == "-n")
    {
      arg++;
      normal_map_filename = argv[arg];

      normal_map_image = std::make_shared<image_32>();
      if (!normal_map_image->load(normal_map_filename))
      {
        std::cout << "Failed to load normal map image \"" << normal_map_filename << "\"\n";
        return 1;
      }
      normal_map = std::make_shared<image_normal_map>(normal_map_image);
      cell_w = normal_map->get_width();
      cell_h = normal_map->get_height();
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
    cell_w = mult_image->get_width();
    cell_h = mult_image->get_height();
    rotating_mult_image = std::make_shared<image_uv_transform>(mult_image);
  }

  if (normal_map)
  {
    rotating_normal_map = std::make_shared<image_uv_transform>(normal_map);
    lighting = std::make_shared<image_lighting>(rotating_normal_map);
    lighting->set_specular_power(200.f);
    lighting->set_diffuse_colour(f_colour(.6f, .6f, 1.f).to_colour());
    lighting->set_ambient_colour(f_colour(.5f, .5f, .5f).to_colour());

  }

  int num_cells = cells_in_x * cells_in_y;
  std::cout << "Num cells: " << num_cells << "\n";
  float degs_per_frame = 360.f / num_cells;

  std::shared_ptr<image> out_image = std::make_shared<image_32>();
  int out_w = cells_in_x * cell_w;
  int out_h = cells_in_y * cell_h;
  out_image->set_size(out_w, out_h);
  out_image->clear(colour(0, 0, 0));

  float degs = 0;  
  for (int i = 0; i < cells_in_y; i++)
  {
    for (int j = 0; j < cells_in_x; j++)
    {
      int x = j * cell_w;
      int y = i * cell_h;
    
      alg3::vec2 centre_of_rot((cell_w - 1) / 2.f, (cell_h - 1) / 2.f);
      alg3::mat3 m = rotation2D(centre_of_rot, -degs);
      if (normal_map)
      {
        rotating_normal_map->set_transform(m); 
      
        normal_map->set_rotation(alg3::rotation2D(alg3::vec2(0, 0), degs));
        //blit<overwrite>(rotating_normal_map, out_image, x, y);
        blit<overwrite>(lighting, out_image, x, y);
      }

      if (rotating_mult_image)
      {
        rotating_mult_image->set_transform(m); 
        blit<add_blend>(rotating_mult_image, out_image, x, y);
      }

      degs += degs_per_frame;
    }
  }

  auto data = dynamic_cast<image_32*>(out_image.get())->get_data();
  lodepng_encode32_file("output.png", data, out_w, out_h); 

  return 0;
}


