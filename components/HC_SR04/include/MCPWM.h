#pragma once
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define HC_SR04_ECHO_GPIO GPIO_NUM_15

class Mcpwm {
private:
  mcpwm_cap_timer_handle_t _timer;
  mcpwm_capture_timer_config_t _timer_config;
  mcpwm_cap_channel_handle_t _channel;
  mcpwm_capture_channel_config_t _channel_config;

public:
  Mcpwm();
  void start();
  static bool mcpwm_callback(mcpwm_cap_channel_handle_t cap_chan,
                             const mcpwm_capture_event_data_t *edata,
                             void *user_data);
};