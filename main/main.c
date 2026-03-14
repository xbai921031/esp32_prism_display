/*
 *    Autor: xbai
 *    Date: 2026/01/17
 */

#include "Os.h"
#include "bsp/bsp_lcd/bsp_lcd.h"
#include "lvgl.h"
#include "app_wifi.h"

void app_main(void)
{
    lv_init();
    bsp_lcd_init();
    wifi_init();
    OS_Init();
    OS_Start();
}