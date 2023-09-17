/**	wifi-captive-portal-esp-idf-component

  Copyright (c) 2021 Jeremy Carter <jeremy@jeremycarter.ca>

  This code is released under the license terms contained in the
  file named LICENSE, which is found in the top-level folder in
  this project. You must agree to follow those license terms,
  otherwise you aren't allowed to copy, distribute, or use any
  part of this project in any way.

  Contains some modified example code from here:
  https://github.com/espressif/esp-idf/blob/release/v4.2/examples/protocols/http_server/simple/main/main.c
  https://github.com/espressif/esp-idf/blob/release/v4.2/examples/protocols/http_server/restful_server/main/rest_server.c

  Original Example Code Header:
  This example code is in the Public Domain (or CC0 licensed, at your option.)

  Unless required by applicable law or agreed to in writing, this
  software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
  CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <fcntl.h>
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs_semihost.h"
#include "esp_vfs_fat.h"
#include "esp_vfs.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "esp_http_server.h"
#include "wifi-captive-portal-esp-idf-httpd.h"
#include "esp_chip_info.h"

#include "esp_random.h"
#include "cJSON.h"

#define REST_CHECK(a, str, goto_tag, ...)                                         \
  do                                                                              \
  {                                                                               \
    if (!(a))                                                                     \
    {                                                                             \
      ESP_LOGE(HTTPD_TAG, "%s(%d): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
      goto goto_tag;                                                              \
    }                                                                             \
  } while (0)

#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + 128)
#define SCRATCH_BUFSIZE (10240)

static const char *HTTPD_TAG = "wifi-captive-portal-esp-idf-httpd";

esp_event_loop_handle_t captive_portal_httpd_event_loop_handle;

ESP_EVENT_DEFINE_BASE(CAPTIVE_PORTAL_HTTPD_EVENT);

static const char *base_path = "/www";

typedef struct rest_server_context
{
  char base_path[ESP_VFS_PATH_MAX + 1];
  char scratch[SCRATCH_BUFSIZE];
} rest_server_context_t;

#define CHECK_FILE_EXTENSION(filename, ext) (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0)

/* Set HTTP response content type according to file extension */
static esp_err_t set_content_type_from_file(httpd_req_t *req, const char *filepath)
{
    const char *type = "text/plain";
    if (CHECK_FILE_EXTENSION(filepath, ".html")) {
        type = "text/html";
    } else if (CHECK_FILE_EXTENSION(filepath, ".js")) {
        type = "application/javascript";
    } else if (CHECK_FILE_EXTENSION(filepath, ".css")) {
        type = "text/css";
    } else if (CHECK_FILE_EXTENSION(filepath, ".png")) {
        type = "image/png";
    } else if (CHECK_FILE_EXTENSION(filepath, ".ico")) {
        type = "image/x-icon";
    } else if (CHECK_FILE_EXTENSION(filepath, ".svg")) {
        type = "text/xml";
    }
    return httpd_resp_set_type(req, type);
}

/* Send HTTP response with the contents of the requested file */
static esp_err_t rest_common_get_handler(httpd_req_t *req)
{
  /*****************************************************************/


  /*****************************************************************/
  size_t req_hdr_host_len = httpd_req_get_hdr_value_len(req, "Host");

  char req_hdr_host_val[req_hdr_host_len + 1];

  esp_err_t res = httpd_req_get_hdr_value_str(req, "Host", (char *)&req_hdr_host_val, sizeof(char) * req_hdr_host_len + 1);
  if (res != ESP_OK)
  {
    ESP_LOGE(HTTPD_TAG, "failed getting HOST header value: %d", res);

    switch (res)
    {
    case ESP_ERR_NOT_FOUND:
      ESP_LOGE(HTTPD_TAG, "failed getting HOST header value: ESP_ERR_NOT_FOUND: Key not found: %d", res);
      break;

    case ESP_ERR_INVALID_ARG:
      ESP_LOGE(HTTPD_TAG, "failed getting HOST header value: ESP_ERR_INVALID_ARG: Null arguments: %d", res);
      break;

    case ESP_ERR_HTTPD_INVALID_REQ:
      ESP_LOGE(HTTPD_TAG, "failed getting HOST header value: ESP_ERR_HTTPD_INVALID_REQ: Invalid HTTP request pointer: %d", res);
      break;

    case ESP_ERR_HTTPD_RESULT_TRUNC:
      ESP_LOGE(HTTPD_TAG, "failed getting HOST header value: ESP_ERR_HTTPD_RESULT_TRUNC: Value string truncated: %d", res);
      break;

    default:
      break;
    }
  }

  ESP_LOGI(HTTPD_TAG, "Got HOST header value: %s", req_hdr_host_val);

  const char redir_trigger_host[] = "connectivitycheck.gstatic.com";

  if (strncmp(req_hdr_host_val, redir_trigger_host, strlen(redir_trigger_host)) == 0)
  {
    const char resp[] = "302 Found";

    ESP_LOGI(HTTPD_TAG, "Detected redirect trigger HOST: %s", redir_trigger_host);

    httpd_resp_set_status(req, resp);

    /** NOTE: This is where you redirect to whatever DNS address you prefer to open the
        captive portal page. This DNS address will be displayed at the top of the
        page, so maybe you want to choose a nice name to use (it can be any legal
        DNS name that you prefer. */
    httpd_resp_set_hdr(req, "Location", "http://wifi-captive-portal");

    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
  }
  else
  {  char filepath[FILE_PATH_MAX];

    rest_server_context_t *rest_context = (rest_server_context_t *)req->user_ctx;
    strlcpy(filepath, rest_context->base_path, sizeof(filepath));

    ESP_LOGW(HTTPD_TAG, "req->uri : %s", req->uri);
    ESP_LOGW(HTTPD_TAG, "filepath : %s", filepath);

    if (req->uri[strlen(req->uri) - 1] == '/') {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else if (strcmp(req->uri, "/hotspot-detect.html") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else if (strcmp(req->uri, "/generate_204") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else if (strcmp(req->uri, "/generate204") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else if (strcmp(req->uri, "/connecttest.txt") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else if (strcmp(req->uri, "/204") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else if(strcmp(req->uri, "/success.txt?ipv4") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));        
    }  else if(strcmp(req->uri, "/edgedl/release2/chrome_component/j2hxfei2occ5siitujtlwgp6xi_3/ojhpjlocmbogdgmfpkhlaaeamibhnphh_3_all_gplutbkdljxxbjolk3siq7kive.crx3") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    }  else if(strcmp(req->uri, "/nm") == 0) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else {
        strlcat(filepath, req->uri, sizeof(filepath));
    }
    ESP_LOGW(HTTPD_TAG, "open file : %s", filepath);

    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1) {
        ESP_LOGE(HTTPD_TAG, "Failed to open file : %s", filepath);
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read existing file");
        return ESP_FAIL;
    }

    set_content_type_from_file(req, filepath);

    char *chunk = rest_context->scratch;
    ssize_t read_bytes;
    do {
        /* Read file in chunks into the scratch buffer */
        read_bytes = read(fd, chunk, SCRATCH_BUFSIZE);
        if (read_bytes == -1) {
            ESP_LOGE(HTTPD_TAG, "Failed to read file : %s", filepath);
        } else if (read_bytes > 0) {
            /* Send the buffer contents as HTTP response chunk */
            if (httpd_resp_send_chunk(req, chunk, read_bytes) != ESP_OK) {
                close(fd);
                ESP_LOGE(HTTPD_TAG, "File sending failed!");
                /* Abort sending file */
                httpd_resp_sendstr_chunk(req, NULL);
                /* Respond with 500 Internal Server Error */
                httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file");
                return ESP_FAIL;
            }
        }
    } while (read_bytes > 0);
    /* Close file after sending complete */
    close(fd);
    ESP_LOGI(HTTPD_TAG, "File sending complete");
    /* Respond with an empty chunk to signal HTTP response completion */
    httpd_resp_send_chunk(req, NULL, 0);
  }

  return ESP_OK;
}

static void start_httpd(void *pvParameter)
{
  /** HTTP server */
  ESP_LOGI(HTTPD_TAG, "Starting HTTP Server...");

  REST_CHECK(base_path, "wrong base path", err);
  rest_server_context_t *rest_context = calloc(1, sizeof(rest_server_context_t));
  REST_CHECK(rest_context, "No memory for rest context", err);
  strlcpy(rest_context->base_path, base_path, sizeof(rest_context->base_path));

  httpd_handle_t server = NULL;

  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.uri_match_fn = httpd_uri_match_wildcard;
  config.lru_purge_enable = true;

  REST_CHECK(httpd_start(&server, &config) == ESP_OK, "Start HTTP server failed", err_start);
  ESP_LOGI(HTTPD_TAG, "Started HTTP Server.");

  ESP_LOGI(HTTPD_TAG, "Registering HTTP server URI handlers...");

    /* URI handler for getting web server files */
    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = rest_common_get_handler,
        .user_ctx = rest_context
    };

  httpd_register_uri_handler(server, &common_get_uri);

  ESP_LOGI(HTTPD_TAG, "Registered HTTP server URI handlers.");
  return;

err_start:
  free(rest_context);

err:
  return;
}

void captive_portal_httpd_task(void *pvParameter)
{
  while (1)
  {
    start_httpd(NULL);

    /** TODO: xEventGroupWaitBits or similar might be much better than vTaskDelay for this section. */
    while (1)
    {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
  }
}
