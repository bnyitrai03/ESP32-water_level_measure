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
  _channel_config.flags.pull_down = false;
  _channel_config.flags.invert_cap_signal = false; // Active high signal
  ESP_ERROR_CHECK(
      mcpwm_new_capture_channel(_timer, &_channel_config, &_channel));
  ESP_LOGI(TAG, "Capture channel registered");
}

// @brief Starts the mcpwm after everything is configured
void Mcpwm::start() {
  ESP_ERROR_CHECK(mcpwm_capture_timer_enable(_timer));
  ESP_ERROR_CHECK(mcpwm_capture_timer_start(_timer));
  ESP_LOGI(TAG, "Capture timer has started working");
}

// Callback function needs to be static
static bool mcpwm_callback(mcpwm_cap_channel_handle_t cap_chan,
                           const mcpwm_capture_event_data_t *edata,
                           void *user_data) {
  static uint32_t cap_val_begin = 0;
  static uint32_t cap_val_end = 0;
  TaskHandle_t task_to_notify = (TaskHandle_t)user_data;
  BaseType_t high_task_wakeup = pdFALSE;

  if (edata->cap_edge == MCPWM_CAP_EDGE_POS) {
    cap_val_begin = edata->cap_value;
    cap_val_end = cap_val_begin;
  } else {
    cap_val_end = edata->cap_value;
    uint32_t tof_ticks = cap_val_end - cap_val_begin;
    xTaskNotifyFromISR(task_to_notify, tof_ticks, eSetValueWithOverwrite,
                       &high_task_wakeup);
  }

  return high_task_wakeup;
}

// @brief Registers the mcpwm callback function
void Mcpwm::register_callback(const TaskHandle_t &task_handle) {
  mcpwm_capture_event_callbacks_t cbs = {
      .on_cap = mcpwm_callback,
  };
  ESP_ERROR_CHECK(mcpwm_capture_channel_register_event_callbacks(_channel, &cbs,
                                                                 task_handle));
  ESP_LOGI(TAG, "Callback registered");

  ESP_ERROR_CHECK(mcpwm_capture_channel_enable(_channel));
  ESP_LOGI(TAG, "Channel enabled");
}