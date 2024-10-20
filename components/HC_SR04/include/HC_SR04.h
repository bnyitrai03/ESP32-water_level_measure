#pragma once
#include "driver/gpio.h"
#include "esp_log.h"

#define HC_SR04_TRIG_GPIO GPIO_NUM_23

class HC_SR04 {
public:
  HC_SR04();

  static void generate_trig();
};