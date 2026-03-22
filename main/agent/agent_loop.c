/*
 * Author: xbai
 * Date  : 2026/03/22
 */

#include "agent_loop.h"
#include "message_bus.h"
#include "llm_proxy.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "DEEPSEEK_ECHO";

void agent_loop(void)
{
    clawbot_msg in[512];
    clawbot_msg out[512];

    if(message_get(in))
    {
        char *reply = llm_chat(in);

        memset(out, 0, sizeof(out));
        snprintf(out, sizeof(out), "%s", reply);
        ESP_LOGI(TAG, "%s", out);

        //message_bus_publish_outbound(&out);
    }
}

