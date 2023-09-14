/**	wifi-captive-portal-esp-idf

  Copyright (c) 2021 Jeremy Carter <jeremy@jeremycarter.ca>

  This code is released under the license terms contained in the
  file named LICENSE, which is found in the top-level folder in
  this project. You must agree to follow those license terms,
  otherwise you aren't allowed to copy, distribute, or use any
  part of this project in any way.
*/
#include "wifi-captive-portal-esp-idf.h"

static const char *TAG = "example";

int app_main(void)
{
  captive_portal();

  return 0;
}
