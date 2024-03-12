#ifdef LO_RES_USE_FRAMEBUFFER

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "framebuffer.h"

framebuffer::framebuffer()
{
  m_filedescriptor = open("/dev/fb0", O_RDWR);
  if (m_filedescriptor == 0) 
  {
    printf("Error: cannot open framebuffer device.\n");
    return;
  }
  printf("The framebuffer device was opened successfully.\n");

  // Get variable screen information
  if (ioctl(m_filedescriptor, FBIOGET_VSCREENINFO, &m_var_info)) 
  {
    printf("Error reading variable information.\n");
  }
  printf("Original %dx%d, %dbpp\n", m_var_info.xres, m_var_info.yres,
         m_var_info.bits_per_pixel );
  printf("xres_virtual: %d, yres_virtual: %d\n", m_var_info.xres_virtual, m_var_info.yres_virtual);

  // Get fixed screen information
  if (ioctl(m_filedescriptor, FBIOGET_FSCREENINFO, &m_fixed_info)) 
  {
    printf("Error reading fixed information.\n");
  }

  // map fb to user mem
  auto screensize = m_fixed_info.smem_len;
  m_pixels = static_cast<uint8_t*>(
    mmap(0,
    screensize,
    PROT_READ | PROT_WRITE,
    MAP_SHARED,
    m_filedescriptor,
    0));

  if (reinterpret_cast<int>(m_pixels) == -1) 
  {
    m_pixels = nullptr;
    printf("Failed to mmap.\n");
    return;
  }
}

framebuffer::~framebuffer()
{
  if (m_pixels)
  {
    munmap(m_pixels, m_fixed_info.smem_len); 
  }

  if (m_filedescriptor != 0)
  {
    close(m_filedescriptor);
  }
}

void framebuffer::set_pixel(int x, int y, uint16_t colour)
{
  size_t pix_offset = 2 * x + y * m_fixed_info.line_length;
  *(m_pixels + pix_offset) = colour & 0xff;
  *(m_pixels + pix_offset + 1) = (colour & 0xff00) >> 8;
}

void framebuffer::set_colour(int x, int y, colour ch) 
{
  uint16_t c = (uint16_t(ch.b) >> 3) | ((uint16_t(ch.g) & 0xfc) << 3) | ((uint16_t(ch.r) & 0xf8) << 8);
  set_pixel(x, y, c);
}

colour framebuffer::get_colour(int x, int y) const 
{
  return {};
}

void framebuffer::clear(colour c) 
{
}

int framebuffer::get_width() const 
{
  return m_var_info.xres;
}

int framebuffer::get_height() const 
{
  return m_var_info.yres;
}

#endif  // LO_RES_USE_FRAMEBUFFER

