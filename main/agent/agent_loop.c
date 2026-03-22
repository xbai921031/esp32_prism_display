/*
 * Author: xbai
 * Date  : 2026/03/22
 */

#include "agent_loop.h"
#include "message_bus.h"
#include "llm_proxy.h"
#include <string.h>

void agent_loop(void)
{
    clawbot_msg_t in;
    clawbot_msg_t out;

    if(message_get(&in))
    {
        char *reply = llm_chat(in.content);

        memset(&out, 0, sizeof(out));
        snprintf(out.content, sizeof(out.content), "%s", reply);

        //message_bus_publish_outbound(&out);
    }
}

