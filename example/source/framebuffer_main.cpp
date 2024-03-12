#ifdef LO_RES_USE_FRAMEBUFFER

#include "colour.h"
#include "font.h"
#include "framebuffer.h"
#include "image.h"
#include "image_8.h"
#include "image_32.h"
#include "pages.h"

p_image the_screen;
font my_font;

int main()
{
  the_screen = std::make_shared<framebuffer>();
  //the_screen->set_size(VIRTUAL_W, VIRTUAL_H);

  //image_8::get_palette().add_colour(colour(0, 0, 0));
  //image_8::get_palette().add_colour(CLEAR_COLOUR);

  // Load a font
  p_image im2 = std::make_shared<image_32>();
  im2->load("assets/font_3x5.png");
  my_font.set_image(im2);
  my_font.set_num_cells(16, 4);

  int page_num = 0;
  while (true)
  {
    for (int i = 0; i < 100; i++)
    {
      the_screen->clear(colour(0, 0, 0)); //CLEAR_COLOUR);
      pages[page_num].draw();
    }
    page_num++;
    if (page_num == pages.size())
    {
      page_num = 0;
    }
  }
}

#endif //  LO_RES_USE_FRAMEBUFFER

