/*
 * Author: xbai
 * Date  : 2026/03/05
 */

#include "Bsp_Lcd.h"
//#include "esp_lcd_panel_vendor.h"
#include "Bsp/Bsp_Lcd/Bsp_Lcd.h"
#include <math.h>

#define LCD_W 240
#define LCD_H 240

static uint16_t framebuffer[LCD_W * LCD_H] __attribute__((aligned(4)));

typedef struct
{
    float radius;
    float angle;
    float speed;
    uint8_t size;
    uint16_t color;
}Planet;

Planet planets[] =
{
    {20,0,0.08,2,0x7BEF}, // Mercury
    {35,0,0.06,3,0xFD20}, // Venus
    {50,0,0.05,3,0x001F}, // Earth
    {65,0,0.04,2,0xF800}, // Mars
    {90,0,0.02,5,0xFFE0}, // Jupiter
};

static void gfx_clear(uint16_t color);
static void gfx_draw_pixel(int x, int y, uint16_t color);
static void gfx_draw_circle(int cx, int cy, int r, uint16_t color);
static void gfx_fill_circle(int cx, int cy, int r, uint16_t color);
static void gfx_present(void);

static void gfx_clear(uint16_t color)
{
    for(int i = 0; i < LCD_W * LCD_H; i++)
    {
        framebuffer[i] = color;
    }
}

static void gfx_draw_pixel(int x, int y, uint16_t color)
{
    if(x < 0 || x >= LCD_W)
    {
        return;
    }

    if(y < 0 || y >= LCD_H)
    {
        return;
    }

    framebuffer[y * LCD_W + x] = color;
}

static void gfx_draw_circle(int cx, int cy, int r, uint16_t color)
{
    for (int i = 0; i < 360; i++)
    {
        float rad = i * 3.14159f / 180.0f;

        int x = cx + r * cosf(rad);
        int y = cy + r * sinf(rad);

        gfx_draw_pixel(x, y, color);
    }
}

static void gfx_fill_circle(int cx, int cy, int r, uint16_t color)
{
    for(int y = -r; y <= r; y++)
    {
        for(int x = -r; x <= r; x++)
        {
            if(x*x + y*y <= r*r)
            {
                gfx_draw_pixel(cx + x, cy + y, color);
            }
        }
    }
}

static void gfx_present(void)
{
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 240, 240, framebuffer);
}

void App_Solar_Render(void)
{
    int cx = 120;
    int cy = 120;

    gfx_clear(0x0000);

    /* Orbit */
    for(int i=0;i<5;i++)
    {
        gfx_draw_circle(cx, cy, planets[i].radius, 0x39E7);
    }

    /* Sun */
    gfx_fill_circle(cx, cy, 12, 0xFFE8);
    gfx_fill_circle(cx, cy, 9, 0xFFF0);
    gfx_fill_circle(cx, cy, 6, 0xFFE0);
    gfx_fill_circle(cx - 2, cy - 2, 2, 0xFFFF);

    for(int i = 0; i < 5; i++)
    {
        planets[i].angle += planets[i].speed;

        int x = cx + planets[i].radius * cosf(planets[i].angle);
        int y = cy + planets[i].radius * sinf(planets[i].angle);

        gfx_fill_circle(x, y, planets[i].size, planets[i].color);
    }

    gfx_present();
}