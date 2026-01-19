/*
 *    Autor: xbai
 *    Date: 2026/01/18
 */

#include "Os.h"
#include "Os_Alarm.h"
#include "esp_rom_sys.h"
#include "Bsp/Bsp_Lcd/Bsp_Lcd.h"

TaskHandle_t OsTask1Handle;
TaskHandle_t OsTask2Handle;
TaskHandle_t OsTask3Handle;

StaticTask_t OsTask1TCB;
StaticTask_t OsTask2TCB;
StaticTask_t OsTask3TCB;

StackType_t OsTask1Stack[2048];
StackType_t OsTask2Stack[2048];
StackType_t OsTask3Stack[2048];

static void OsTask1(void* arg)
{
    while(1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        bsp_lcd_fill_color(0xF800); /* Red */
        //esp_rom_printf("[Task1] time=%llu\r\n", esp_timer_get_time());
    }
}

static void OsTask2(void* arg)
{
    while(1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        bsp_lcd_fill_color(0x07E0); /* Green */
        //esp_rom_printf("[Task2] time=%llu\r\n", esp_timer_get_time());
    }
}

static void OsTask3(void* arg)
{
    while(1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        bsp_lcd_fill_color(0x001F); /* Blue */
        //esp_rom_printf("[Task2] time=%llu\r\n", esp_timer_get_time());
    }
}

void OS_Init(void)
{
    OsTask1Handle = xTaskCreateStatic(
        OsTask1,
        "OsTask1",
        2048,
        NULL,
        4,
        OsTask1Stack,
        &OsTask1TCB);

    OsTask2Handle = xTaskCreateStatic(
        OsTask2,
        "OsTask2",
        2048,
        NULL,
        3,
        OsTask2Stack,
        &OsTask2TCB);

    OsTask3Handle = xTaskCreateStatic(
        OsTask3,
        "OsTask3",
        2048,
        NULL,
        3,
        OsTask3Stack,
        &OsTask3TCB);
}

void OS_Start(void)
{
    Os_AlarmInit();
}
