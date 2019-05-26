/*
 * @author: Theodor Fragner (theodor[at]fragner.org)
 * @date  : May, 24. 2019
 * @file  : gfx.c
 * @descr : source file for primitive graphics
 *          library
 */

#include "gfx.h"

void fill_buffer()
{
    for(int x=0; x<DISP_WIDTH; x++)
    {
        for(int y=0; y<DISP_HEIGHT; y++)
        {
            draw_pixel(x, y);
        }
    }
}

void draw_pixel(uint16_t x, uint16_t y)
{
    framebuffer[y * DISP_WIDTH + x] = ili_color;
}

void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    for(int xpos=x; xpos<x+width; xpos++)
    {
        draw_pixel(xpos, y);
        draw_pixel(xpos, y+height-1);
    }
    for(int ypos=y; ypos<y+height; ypos++)
    {
        draw_pixel(x, ypos);
        draw_pixel(x+width-1, ypos);
    }
}

void draw_circle(uint16_t x, uint16_t y, uint16_t radius)
{
    for(uint16_t angle=0; angle<360; angle++)
        draw_pixel(sin(angle)*radius+x, cos(angle)*radius+y);
}

void draw_img(char* data, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t no_alpha)
{
    for (int ypos=MAX(y, 0); ypos<MIN(height+y, DISP_HEIGHT); ypos++)
    {
        if(x < 0)
            data += 4 * -x;
        
        for (int xpos=MAX(x, 0); xpos<MIN(width+x, DISP_WIDTH); xpos++)
        {
            set_color((((data[0] - 33) << 2) | ((data[1] - 33) >> 4)), ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)), ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))));
            if((ili_color != 0) || no_alpha)
                draw_pixel(xpos, ypos);
            data += 4;
        }
        
        if(width + x > DISP_WIDTH)
            data += 4 * (width + x - DISP_WIDTH);
    }
}

void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float alpha)
{
    uint8_t fill_color[3] = {rgb_color[0], rgb_color[1], rgb_color[2]};
    for(int xpos=x; xpos<x+width; xpos++)
    {
        for(int ypos=y; ypos<y+height; ypos++)
        {
            get_color(xpos, ypos);
            set_color(alpha*fill_color[0]+(1-alpha)*rgb_color[0], alpha*fill_color[1]+(1-alpha)*rgb_color[1], alpha*fill_color[2]+(1-alpha)*rgb_color[2]);
            draw_pixel(xpos, ypos);
        }
    }
    set_color(fill_color[0], fill_color[1], fill_color[2]);
}

void fill_circle(uint16_t x, uint16_t y, uint16_t radius, float alpha)
{
    uint8_t fill_color[3] = {rgb_color[0], rgb_color[1], rgb_color[2]};
    for(uint16_t xpos=x-radius; xpos<x+radius; xpos++)
    {
        for(uint16_t ypos=y-sqrt(radius*radius-(x-xpos)*(x-xpos)); ypos<y+sqrt(radius*radius-(x-xpos)*(x-xpos)); ypos++)
        {
            get_color(xpos, ypos);
            set_color(alpha*fill_color[0]+(1-alpha)*rgb_color[0], alpha*fill_color[1]+(1-alpha)*rgb_color[1], alpha*fill_color[2]+(1-alpha)*rgb_color[2]);
            draw_pixel(xpos, ypos);
        }
    }
    set_color(fill_color[0], fill_color[1], fill_color[2]);
}

void set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    ili_color = to_bgr(red, green, blue);
    rgb_color[0] = red;
    rgb_color[1] = green;
    rgb_color[2] = blue;
}

void get_color(uint16_t x, uint16_t y)
{
    ili_color = framebuffer[y * DISP_WIDTH + x];
    from_bgr(ili_color, rgb_color);
}