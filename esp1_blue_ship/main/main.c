/**	wifi-captive-portal-esp-idf

  Copyright (c) 2021 Jeremy Carter <jeremy@jeremycarter.ca>

  This code is released under the license terms contained in the
  file named LICENSE, which is found in the top-level folder in
  this project. You must agree to follow those license terms,
  otherwise you aren't allowed to copy, distribute, or use any
  part of this project in any way.
*/
#include "wifi-captive-portal-esp-idf.h"
#include "rgb_led.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"

static const char *TAG = "example";

void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

void flash_yellow(void);

int app_main(void)
{
  rgb_led_configure();
  rgb_led_set_color(0, 0, 128);
  captive_portal();

  ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));

  return 0;
}

void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
  if (event_id == WIFI_EVENT_AP_STACONNECTED)
  {
    wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
    ESP_LOGI(TAG, "station " MACSTR " join, AID=%d", MAC2STR(event->mac), event->aid);

    // Client MAC: 7c:df:a1:d5:c2:a8
    if (!(event->mac[0] == 0x7c && event->mac[1] == 0xdf && event->mac[2] == 0xa1 && event->mac[3] == 0xd5 && event->mac[4] == 0xc2 && event->mac[5] == 0xa8))
    {
      flash_yellow();
    }
    else
    {
      rgb_led_set_color(255, 255, 255);
      vTaskDelay(pdMS_TO_TICKS(200));
    }
    rgb_led_set_color(0, 0, 128);
  }
  else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
  {
    // Dont do anything for now
  }
}

void flash_yellow(void)
{
  rgb_led_set_color(128, 128, 0);
  vTaskDelay(pdMS_TO_TICKS(200));
  rgb_led_turn_off();
  vTaskDelay(pdMS_TO_TICKS(200));
  rgb_led_set_color(128, 128, 0);
  vTaskDelay(pdMS_TO_TICKS(200));
  rgb_led_turn_off();
  vTaskDelay(pdMS_TO_TICKS(200));
  rgb_led_set_color(128, 128, 0);
  vTaskDelay(pdMS_TO_TICKS(200));
  rgb_led_turn_off();
}