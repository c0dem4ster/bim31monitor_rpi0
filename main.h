/*
 * @author: Theodor Fragner (theodor[at]fragner.org)
 * @date  : May, 24. 2019
 * @file  : main.c
 * @descr : header file for making framebuffer
 *          available to graphics library
 */

#include <stdint.h>

#define DISP_WIDTH 320
#define DISP_HEIGHT 240

#define FB_DEVICE "/dev/fb1"

#define MAX(A, B) ((A)>(B)?(A):(B))
#define MIN(A, B) ((A)<(B)?(A):(B))

// pointer to the framebuffer
uint16_t *framebuffer;

// convert RGB888 to BGR565
uint16_t to_bgr(uint8_t r, uint8_t g, uint8_t b);

// convert BGR565 to RGB888
void from_bgr(uint16_t bgr, uint8_t* rgb);