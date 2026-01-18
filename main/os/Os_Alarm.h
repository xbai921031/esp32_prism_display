/*
 *    Autor: xbai
 *    Date: 2026/01/18
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

typedef struct
{
    TaskHandle_t* task;
    uint64_t offset_us;
    uint64_t period_us;
    esp_timer_handle_t timer;
}Os_Alarm_t;

extern TaskHandle_t OsTask1Handle;
extern TaskHandle_t OsTask2Handle;

static Os_Alarm_t OsAlarmTable[] =
{
    {
        .task = &OsTask1Handle,
        .offset_us = 1 * 1000,    /* 1ms offset */
        .period_us = 10 * 1000,   /* 10ms period */
    },
    {
        .task = &OsTask2Handle,
        .offset_us = 6 * 1000,    /* 6ms offset */
        .period_us = 10 * 1000,   /* 10ms period */
    }
};

#define OS_ALARM_NUM (sizeof(OsAlarmTable) / sizeof(OsAlarmTable[0]))

void Os_AlarmInit(void);
