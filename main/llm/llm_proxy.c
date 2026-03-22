/*
 * Author: xbai
 * Date  : 2026/03/22
 */

#include "llm_proxy.h"
#include "clawbot_config.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 2048

static char response_buffer[BUF_SIZE];

char* llm_chat(const char* input)
{
    char request[512];

    snprintf(request, sizeof(request),
        "{"
        "\"model\":\"deepseek-chat\","
        "\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}]"
        "}",
        input
    );

    esp_http_client_config_t config = {
        .url = DEEPSEEK_URL,
        .method = HTTP_METHOD_POST,
        .timeout_ms = 10000,
        .skip_cert_common_name_check = true,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_header(client, "Authorization", "Bearer " DEEPSEEK_API_KEY);

    esp_http_client_set_post_field(client, request, strlen(request));

    esp_http_client_perform(client);

    int len = esp_http_client_read_response(client, response_buffer, BUF_SIZE - 1);
    response_buffer[len] = 0;

    esp_http_client_cleanup(client);

    // JSON parse
    cJSON *root = cJSON_Parse(response_buffer);
    if(!root)
    {
        return "JSON parse error";
    }

    cJSON *choices = cJSON_GetObjectItem(root, "choices");
    cJSON *first = cJSON_GetArrayItem(choices, 0);
    cJSON *message = cJSON_GetObjectItem(first, "message");
    cJSON *content = cJSON_GetObjectItem(message, "content");

    static char reply[512];
    snprintf(reply, sizeof(reply), "%s", content->valuestring);

    cJSON_Delete(root);

    return reply;
}