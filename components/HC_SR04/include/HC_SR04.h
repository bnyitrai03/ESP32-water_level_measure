#pragma once
#include "esp_log.h"
#include "esp_private/esp_clk.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define HC_SR04_TRIG_GPIO GPIO_NUM_23
#define HC_SR04_ECHO_GPIO GPIO_NUM_15