/*
 *    Autor: xbai
 *    Date: 2026/01/17
 */

#include "Os.h"
#include "Bsp/Bsp_Lcd/Bsp_Lcd.h"

void app_main(void)
{
    bsp_lcd_init();
    OS_Init();
    OS_Start();
}