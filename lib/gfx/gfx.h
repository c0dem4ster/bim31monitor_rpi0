/*
 * @author: Theodor Fragner (theodor[at]fragner.org)
 * @date  : May, 24. 2019
 * @file  : gfx.h
 * @descr : header file for primitive graphics
 *          library
 */

#ifndef GFX_INCLUDED
#define GFX_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../../main.h"

// fill framebuffer with color
void fill_buffer();

// set pixel at specified coordinates to color
void draw_pixel(uint16_t x, uint16_t y);

// draw a rectangle
void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

// draw a circle
void draw_circle(uint16_t x, uint16_t y, uint16_t radius);

// draw an image (gimp header exporter)
void draw_img(char* data, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t no_alpha);

// fill a rectangle
void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float alpha);

// fill a circle
void fill_circle(uint16_t x, uint16_t y, uint16_t radius, float alpha);

// convert rgb color range to 16 bit format
void set_color(uint8_t red, uint8_t green, uint8_t blue);

// get display color at specified coordinate
void get_color(uint16_t x, uint16_t y);

// current selected color BGR565
uint16_t ili_color;

// current selected color RGB888
uint8_t rgb_color[3];

#endif // GFX_INCLUDED
