# wifi-captive-portal-esp-idf-component
#
# Copyright (c) 2021 Jeremy Carter <jeremy@jeremycarter.ca>
#
# This code is released under the license terms contained in the
# file named LICENSE, which is found in the top-level folder in
# this project. You must agree to follow those license terms,
# otherwise you aren't allowed to copy, distribute, or use any
# part of this project in any way.

idf_component_register(
  SRCS
    "wifi-captive-portal-esp-idf.c"
    "wifi-captive-portal-esp-idf-dns.c"
    "wifi-captive-portal-esp-idf-httpd.c"
    "wifi-captive-portal-esp-idf-wifi.c"

  REQUIRES
    esp_event esp_netif esp_wifi nvs_flash vfs fatfs esp_http_server json spiffs

  INCLUDE_DIRS
    "include"
)

set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)

# Frontend partition handling
set(WEB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frontend)
if(EXISTS ${WEB_SRC_DIR}/build)
    spiffs_create_partition_image(www ${WEB_SRC_DIR}/build FLASH_IN_PROJECT)
else()
    message(FATAL_ERROR "${WEB_SRC_DIR}/build doesn't exit. Please run 'npm run build' in ${WEB_SRC_DIR}")
endif()