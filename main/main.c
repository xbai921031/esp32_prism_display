/*
 *    Autor: xbai
 *    Date: 2026/01/17
 */

#include "Os.h"
#include "lcd.h"
#include "lvgl.h"
#include "wifi.h"
#include "ws_server.h"
#include "message_bus.h"
//#include "esp_crt_bundle.h"

void app_main(void)
{
    lv_init();
    lcd_init();
    wifi_init();
    start_ws_server();
    message_bus_init();
    //esp_crt_bundle_attach(NULL);
    OS_Init();
    OS_Start();
}