#ifndef FIREBASE_API_H
#define FIREBASE_API_H

#include "esp_err.h"

esp_err_t firebase_post(const char *data);
esp_err_t firebase_get();

#endif