/**	wifi-captive-portal-esp-idf-component

  Copyright (c) 2021 Jeremy Carter <jeremy@jeremycarter.ca>

  This code is released under the license terms contained in the
  file named LICENSE, which is found in the top-level folder in
  this project. You must agree to follow those license terms,
  otherwise you aren't allowed to copy, distribute, or use any
  part of this project in any way.
*/
#include "esp_vfs_fat.h"
#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "wifi-captive-portal-esp-idf.h"

const char *TAG = "wifi-captive-portal-esp-idf";

const char *captive_portal_wifi_task_name = "captive_portal_wifi_task";
const uint32_t captive_portal_wifi_task_stack_depth = 4096;
UBaseType_t captive_portal_wifi_task_priority = 5;

const char *captive_portal_httpd_task_name = "captive_portal_httpd_task";
const uint32_t captive_portal_httpd_task_stack_depth = 4096;
UBaseType_t captive_portal_httpd_task_priority = 5;

const char *captive_portal_task_name = "captive_portal_task";

/** Initialize the task. */
static void captive_portal_task_init(void)
{
}

/** Clean up the task. */
static void captive_portal_task_cleanup(void)
{
}

static void captive_portal_wifi_stopped_event_handler(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data)
{
  ESP_LOGI(TAG, "event received: CAPTIVE_PORTAL_WIFI_EVENT_STOPPED");
}

static void captive_portal_wifi_finish_event_handler(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data)
{
  ESP_LOGI(TAG, "event received: CAPTIVE_PORTAL_WIFI_EVENT_FINISH");

  xTaskCreate(&captive_portal_httpd_task, captive_portal_httpd_task_name, captive_portal_httpd_task_stack_depth * 8, NULL, captive_portal_httpd_task_priority, NULL);
  ESP_LOGI(TAG, "Task started: %s", captive_portal_httpd_task_name);
}

static void captive_portal_httpd_finish_event_handler(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data)
{
  ESP_LOGI(TAG, "event received: CAPTIVE_PORTAL_HTTPD_EVENT_FINISH");
}

/** The main task. */
void captive_portal_task(void *pvParameter)
{
  struct timeval now;
  gettimeofday(&now, NULL);

  ESP_LOGI(TAG, "task %s is running", captive_portal_task_name);

  ESP_LOGI(TAG, "%s loop", captive_portal_task_name);

  captive_portal_task_init();

  captive_portal_task_cleanup();
}

esp_err_t init_fs(void)
{
  esp_vfs_spiffs_conf_t conf = {
      .base_path = "/www",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = false};

  esp_err_t ret = esp_vfs_spiffs_register(&conf);
  if (ret != ESP_OK)
  {
    if (ret == ESP_FAIL)
    {
      ESP_LOGE(TAG, "Failed to mount or format filesystem");
    }
    else if (ret == ESP_ERR_NOT_FOUND)
    {
      ESP_LOGE(TAG, "Failed to find SPIFFS partition");
    }
    else
    {
      ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
    }
    return ESP_FAIL;
  }

  size_t total = 0, used = 0;
  ret = esp_spiffs_info(NULL, &total, &used);
  if (ret != ESP_OK)
  {
    ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
  }
  else
  {
    ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
  }
  return ESP_OK;
}

void captive_portal(void)
{
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(init_fs());

  esp_event_loop_args_t captive_portal_wifi_event_loop_args = {
      .queue_size = 5,
      .task_name = "captive_portal_wifi_event_loop_task", // task will be created
      .task_priority = uxTaskPriorityGet(NULL),
      .task_stack_size = captive_portal_wifi_task_stack_depth,
      .task_core_id = tskNO_AFFINITY};

  ESP_ERROR_CHECK(esp_event_loop_create(&captive_portal_wifi_event_loop_args, &captive_portal_wifi_event_loop_handle));
  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(captive_portal_wifi_event_loop_handle, CAPTIVE_PORTAL_WIFI_EVENT, CAPTIVE_PORTAL_WIFI_EVENT_FINISH, captive_portal_wifi_finish_event_handler, captive_portal_wifi_event_loop_handle, NULL));
  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(captive_portal_wifi_event_loop_handle, CAPTIVE_PORTAL_WIFI_EVENT, CAPTIVE_PORTAL_WIFI_EVENT_STOPPED, captive_portal_wifi_stopped_event_handler, captive_portal_wifi_event_loop_handle, NULL));

  esp_event_loop_args_t captive_portal_httpd_event_loop_args = {
      .queue_size = 5,
      .task_name = "captive_portal_httpd_event_loop_task", // task will be created
      .task_priority = uxTaskPriorityGet(NULL),
      .task_stack_size = captive_portal_httpd_task_stack_depth,
      .task_core_id = tskNO_AFFINITY};

  ESP_ERROR_CHECK(esp_event_loop_create(&captive_portal_httpd_event_loop_args, &captive_portal_httpd_event_loop_handle));
  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(captive_portal_httpd_event_loop_handle, CAPTIVE_PORTAL_HTTPD_EVENT, CAPTIVE_PORTAL_HTTPD_EVENT_FINISH, captive_portal_httpd_finish_event_handler, captive_portal_httpd_event_loop_handle, NULL));

  xTaskCreate(&captive_portal_wifi_task, captive_portal_wifi_task_name, captive_portal_wifi_task_stack_depth * 8, NULL, captive_portal_wifi_task_priority, NULL);
  ESP_LOGI(TAG, "Task started: %s", captive_portal_wifi_task_name);
}
