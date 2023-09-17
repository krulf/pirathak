#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "myWifi.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"

#include "lwip/err.h"
#include "lwip/sys.h"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

#define MAX_RETRY 5

static const char *TAG = "wifi station";

static int s_retry_num = 0;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    // else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    // {
    //     if (s_retry_num < MAX_RETRY)
    //     {
    //         esp_wifi_connect();
    //         s_retry_num++;
    //         ESP_LOGI(TAG, "retry to connect to the AP");
    //     }
    //     else
    //     {
    //         xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
    //     }
    //     ESP_LOGI(TAG, "connect to the AP fail");
    // }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

esp_err_t init_wifi(char *set_ssid, char *set_password)
{
    esp_err_t ret = ESP_OK;
    ESP_LOGI("TEST", "xEventGroupCreate");
    s_wifi_event_group = xEventGroupCreate();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_LOGI("TEST", "esp_wifi_init");
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            //            .ssid = (uint8_t *)set_ssid,
            //            .password = (uint8_t *)set_password,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    strcpy((char *)wifi_config.sta.ssid, set_ssid);
    strcpy((char *)wifi_config.sta.password, set_password);
    ESP_LOGI("TEST", "esp_wifi_set_mode");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 set_ssid, set_password);
    }
    else if (bits & WIFI_FAIL_BIT)
    {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 set_ssid, set_password);
    }
    else
    {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }

    /* The event will not be processed after unregister */
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
    vEventGroupDelete(s_wifi_event_group);
    return ret;
}

void stop_wifi(void)
{
    ESP_LOGI("TEST", "esp_wifi_disconnect");
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    ESP_LOGI("TEST", "esp_wifi_stop");
    ESP_ERROR_CHECK(esp_wifi_stop());
    ESP_LOGI("TEST", "esp_wifi_deinit");
    ESP_ERROR_CHECK(esp_wifi_deinit());
}