#ifndef __CAPTIVE_PORTAL_COMPONENT_CAPTIVE_PORTAL_WIFI_H_INCLUDED__
#define __CAPTIVE_PORTAL_COMPONENT_CAPTIVE_PORTAL_WIFI_H_INCLUDED__
/**	wifi-captive-portal-esp-idf-component

  Copyright (c) 2021 Jeremy Carter <jeremy@jeremycarter.ca>

  This code is released under the license terms contained in the
  file named LICENSE, which is found in the top-level folder in
  this project. You must agree to follow those license terms,
  otherwise you aren't allowed to copy, distribute, or use any
  part of this project in any way.
*/
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_event_base.h"
#include "wifi-captive-portal-esp-idf-dns.h"

/** An event base type for "wifi-captive-portal-esp-idf-wifi". */
ESP_EVENT_DECLARE_BASE(CAPTIVE_PORTAL_WIFI_EVENT);
enum /**< The events. */
{
  CAPTIVE_PORTAL_WIFI_EVENT_FINISH,  /**< An event for "this task is finished". */
  CAPTIVE_PORTAL_WIFI_EVENT_STOPPED, /**< Do something after the wifi interface has stopped. */
};

/** The event loop handle. */
extern esp_event_loop_handle_t captive_portal_wifi_event_loop_handle;

/** Task action IDs of actions this task can perform. */
enum captive_portal_wifi_task_action_id
{
  CAPTIVE_PORTAL_WIFI_TASK_ACTION_CONNECT = 1U, /**< Initialize (if necessary), and connect to a wifi network. */
  CAPTIVE_PORTAL_WIFI_TASK_ACTION_DISCONNECT,   /**< Disconnect the wifi interface. */
  CAPTIVE_PORTAL_WIFI_TASK_ACTION_STOP,         /**< Disconnect and stop the wifi interface. */
};

/** Task action values. */
struct captive_portal_wifi_task_action_value_t
{
  bool no_deep_sleep;        /**< If true, don't deep sleep after the wifi request. */
  uint64_t deep_sleep_usecs; /**< Deep sleep for this number of microseconds (seconds * 1000000). */
};

typedef void *captive_portal_wifi_task_action_value_void_p;

#define _CAPTIVE_PORTAL_WIFI_TASK_ACTION_VALUE_CAST_VOID_P(x) (captive_portal_wifi_task_action_value_void_p) & x
#define CAPTIVE_PORTAL_WIFI_TASK_ACTION_VALUE_CAST_VOID_P(x) _CAPTIVE_PORTAL_WIFI_TASK_ACTION_VALUE_CAST_VOID_P(x)

#define _CAPTIVE_PORTAL_WIFI_TASK_ACTION_VALUE_COPY(x) *(struct captive_portal_wifi_task_action_value_t *)x
#define CAPTIVE_PORTAL_WIFI_TASK_ACTION_VALUE_COPY(x) _CAPTIVE_PORTAL_WIFI_TASK_ACTION_VALUE_COPY(x)

/** Task actions. */
struct captive_portal_wifi_task_action_t
{
  enum captive_portal_wifi_task_action_id id;
  captive_portal_wifi_task_action_value_void_p value;
};

typedef void *captive_portal_wifi_task_action_void_p;

#define _CAPTIVE_PORTAL_WIFI_TASK_ACTION_CAST_VOID_P(x) (captive_portal_wifi_task_action_void_p) & x
#define CAPTIVE_PORTAL_WIFI_TASK_ACTION_CAST_VOID_P(x) _CAPTIVE_PORTAL_WIFI_TASK_ACTION_CAST_VOID_P(x)

#define _CAPTIVE_PORTAL_WIFI_TASK_ACTION_COPY(x) *(struct captive_portal_wifi_task_action_t *)x
#define CAPTIVE_PORTAL_WIFI_TASK_ACTION_COPY(x) _CAPTIVE_PORTAL_WIFI_TASK_ACTION_COPY(x)

#ifdef __cplusplus
extern "C"
{
#endif

  /** The esp-idf task function. */
  void captive_portal_wifi_task(void *pvParameter);

#ifdef __cplusplus
}
#endif

#endif
