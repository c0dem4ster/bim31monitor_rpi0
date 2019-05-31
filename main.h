/*
 * @author: Theodor Fragner (theodor[at]fragner.org)
 * @date  : May, 24. 2019
 * @file  : main.c
 * @descr : header file for making framebuffer
 *          available to graphics library
 */

#include <stdint.h>

#define FB_DEVICE "/dev/fb0"

uint16_t* framebuffer;

// convert RGB888 to BGR565
void set_pixel(uint16_t x, uint16_t y, uint8_t* c);

// convert BGR565 to RGB888
void set_pixel(uint16_t x, uint16_t y, uint8_t* c);
