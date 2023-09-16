#include "string.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "esp_wifi.h"
#include "myWifi.h"
#include "esp_log.h"

#define DELAY 500 // ms

static const char *TAG = "ESP-Client";

void app_main(void)
{
  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  ESP_LOGI("TEST", "esp_netif_create_default_wifi_sta");
  esp_netif_create_default_wifi_sta();

  init_wifi("Green Ship", "stjerner");
  vTaskDelay(pdMS_TO_TICKS(DELAY));

  while (1)
  {
    stop_wifi();
    init_wifi("Blue Ship", "kikkerter");
    vTaskDelay(pdMS_TO_TICKS(DELAY));
    stop_wifi();
    init_wifi("Red Ship", "skattekort");
    vTaskDelay(pdMS_TO_TICKS(DELAY));
    stop_wifi();
    init_wifi("Green Ship", "stjerner");
    vTaskDelay(pdMS_TO_TICKS(DELAY));
  }
}
