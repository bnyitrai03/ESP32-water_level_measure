#include "esp_log.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "HC_SR04.h"
#include "main.h"

static const char *TAG = "main";

static volatile uint32_t rising_edge_time = 0;
static volatile int interrupt_count = 0;
static volatile bool new_measurement = false;

/* static bool IRAM_ATTR mcpwm_callback(mcpwm_cap_channel_handle_t cap_chan,
                                     const mcpwm_capture_event_data_t *edata,
                                     void *user_data) {
  BaseType_t high_task_wakeup = pdTRUE;
  interrupt_count++;
  return high_task_wakeup;
} */

void run_main() {
  HC_SR04 sensor;

  ESP_LOGI(TAG, "Initial ECHO pin state: %d",
           gpio_get_level(HC_SR04_ECHO_GPIO));
  ESP_LOGI(TAG, "Initial TRIG pin state: %d",
           gpio_get_level(HC_SR04_TRIG_GPIO));

  sensor.timer.register_callback(xTaskGetCurrentTaskHandle());
  sensor.timer.start();

  uint32_t tof_ticks;

  while (true) {
    sensor.generate_trig();
    if (xTaskNotifyWait(0x00, ULONG_MAX, &tof_ticks, pdMS_TO_TICKS(1000)) ==
        pdTRUE) {
      float pulse_width_us = tof_ticks * (1000000.0 / APB_CLK_FREQ);
      if (pulse_width_us > 35000) {
        ESP_LOGI(TAG, "Distance is bigger than 400 cm");
        continue;
      }
      float distance = pulse_width_us / 58.0;
      ESP_LOGI(TAG, "Measured distance: %.2f cm", distance);
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

extern "C" void app_main(void) { run_main(); }