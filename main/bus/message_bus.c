/*
 * Author: xbai
 * Date  : 2026/03/22
 */

#include "message_bus.h"

static QueueHandle_t msg_q;

void message_bus_init(void)
{
    msg_q = xQueueCreate(5, sizeof(clawbot_msg));
}

/* Agent -> Remote LLM */
int message_get(clawbot_msg *msg)
{
    return xQueueReceive(msg_q, msg, portMAX_DELAY);
}

/* WebSocket -> Agent */
int message_publish(clawbot_msg *msg)
{
    return xQueueSend(msg_q, msg, portMAX_DELAY);
}