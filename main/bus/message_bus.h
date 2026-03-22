/*
 *    Autor: xbai
 *    Date: 2026/03/22
 */

#pragma once


#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef struct
{
    char content[512];
}clawbot_msg_t;

void message_bus_init(void);
int message_get(clawbot_msg_t *msg);
int message_publish(clawbot_msg_t *msg);
