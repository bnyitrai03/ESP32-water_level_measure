#pragma once
#include "driver/gpio.h"
#include "driver/mcpwm_cap.h"
#include "driver/mcpwm_prelude.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define HC_SR04_ECHO_GPIO GPIO_NUM_15

class Mcpwm {
public:
  Mcpwm();
  void start();
  void register_callback(const TaskHandle_t &task_handle);

private:
  mcpwm_cap_timer_handle_t _timer = nullptr;
  mcpwm_cap_channel_handle_t _channel = nullptr;
  mcpwm_capture_timer_config_t _timer_config = {};
  mcpwm_capture_channel_config_t _channel_config = {};
};