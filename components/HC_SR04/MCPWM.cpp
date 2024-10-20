#include "MCPWM.h"

static const char *TAG = "MCPWM";

Mcpwm::Mcpwm() {
  _timer_config.clk_src = MCPWM_CAPTURE_CLK_SRC_DEFAULT;
  _timer_config.group_id = 0;
  ESP_ERROR_CHECK(mcpwm_new_capture_timer(&_timer_config, &_timer));
  ESP_LOGI(TAG, "Capture timer registered");

  _channel_config.gpio_num = HC_SR04_ECHO_GPIO;
  _channel_config.prescale = 1;
  _channel_config.flags.neg_edge = true; // capture on both edges
  _channel_config.flags.pos_edge = true;
  _channel_config.flags.pull_up = true; // internal pullup
  ESP_ERROR_CHECK(
      mcpwm_new_capture_channel(_timer, &_channel_config, &_channel));
  ESP_LOGI(TAG, "Capture channel registered");

  TaskHandle_t init_task = xTaskGetCurrentTaskHandle();
  mcpwm_capture_event_callbacks_t cbs = {.on_cap = mcpwm_callback};
  ESP_ERROR_CHECK(mcpwm_capture_channel_register_event_callbacks(_channel, &cbs,
                                                                 init_task));
  ESP_LOGI(TAG, "Callback of mcpwm has been registered");

  ESP_ERROR_CHECK(mcpwm_capture_channel_enable(_channel));
  ESP_LOGI(TAG, "Enabled the capture channel");
}

void Mcpwm::start() {
  ESP_ERROR_CHECK(mcpwm_capture_timer_enable(_timer));
  ESP_ERROR_CHECK(mcpwm_capture_timer_start(_timer));
  ESP_LOGI(TAG, "Capture timer has started working");
}

bool Mcpwm::mcpwm_callback(mcpwm_cap_channel_handle_t cap_chan,
                           const mcpwm_capture_event_data_t *edata,
                           void *user_data) {
  // Implement callback logic here
  // For now, just log that the callback was called
  ESP_LOGI(TAG, "MCPWM callback called");
  return true;
}