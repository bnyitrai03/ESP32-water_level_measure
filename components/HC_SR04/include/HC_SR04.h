#pragma once
#include "MCPWM.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define HC_SR04_TRIG_GPIO GPIO_NUM_23

class HC_SR04 {
private:
  float distance_cm;

public:
  Mcpwm timer;

  HC_SR04();

  float get_distance() { return distance_cm; }
  static void generate_trig();
};