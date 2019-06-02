/*
 * @author: Theodor Fragner (theodor[at]fragner.org)
 * @date  : May, 24. 2019
 * @file  : main.c
 * @descr : program reads content from text file
 *          and outputs it graphically to a
 *          framebuffer device
 */

#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>

#include "main.h"

#include "embedded-library/gfx/gfx.h"
#include "embedded-library/util/util.h"

#include "img/background.h"
#include "img/rssi.h"
#include "img/tram.h"
#include "img/ulf.h"

void set_pixel(uint16_t x, uint16_t y, uint8_t c[3])
{
  framebuffer[y * DISP_WIDTH + x] = (c[0] & 0xf8) << 8 |
                                    (c[1] & 0xfc) << 3 |
                                    (c[2] & 0xf8) >> 3;
}

void get_pixel(uint16_t x, uint16_t y, uint8_t c[3])
{
  uint16_t bgr = framebuffer[y * DISP_WIDTH + x];
  c[0] = (bgr >> 8) & 0xf8;
  c[1] = (bgr >> 3) & 0xfc;
  c[2] = (bgr << 3) & 0xf8;
}

void get_data(uint8_t* countdowns, uint8_t* ulfs)
{
  char* line = malloc(10);
  FILE* fp = fopen("data", "r");

  if(fp == NULL)
    printf("no data file found!\n");
    return;

  for(int i = 0; i < 3; i++)
  {
    fgets(line, 9, fp);
    sscanf(line, "%d", &countdowns[i]);
    fgets(line, 9, fp);
    ulfs[i] = line[0] == 'T' ? 1 : 0;
  }
}

int main()
{
  // received data gets stored here
  uint8_t countdowns[3], ulfs[3];

  // file descriptor for framebuffer
  int fd;
  
  gfx_init(&set_pixel, &get_pixel);

  // read received data from file
  get_data(countdowns, ulfs);

  // open framebuffer device
  fd = open(FB_DEVICE, O_RDWR);

  // map memory region of framebuffer
  framebuffer = mmap(0, DISP_WIDTH * DISP_HEIGHT * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  // set display background to black
  set_color(0, 0, 0);
  fill_buffer();

  // draw status bar
  draw_img(background, 0, 0, background_width, background_height, 1);

  // draw vertical lines
  set_color(0xff, 0xff, 0xff);
  for(int i = 0; i < 4; i++)
    fill_rect(29 + 90 * i, rssi_height, 1, DISP_HEIGHT - rssi_height, 1);

  // draw trams
  for(int i = 0; i < 3; i++)
    draw_img(
      ulfs[i] ? ulf : tram,
      300 - 18 * countdowns[i] - tram_width,
      rssi_height + 30 + i*60,
      ulfs[i] ? ulf_width : tram_width,
      ulfs[i] ? ulf_height : tram_height, 0);

  // draw signal strength icon
  draw_img(rssi[1], DISP_WIDTH - rssi_width, 0, rssi_width, rssi_height, 0);

  // unmap framebuffer and close device
  munmap(framebuffer, DISP_WIDTH * DISP_HEIGHT * 2);
  close(fd);

  // exit with success code
  return EXIT_SUCCESS;
}
