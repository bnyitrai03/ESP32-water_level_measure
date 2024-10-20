#include "esp_log.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "HC_SR04.h"
#include "MCPWM.h"
#include "main.h"

static const char *TAG = "main";

void run_main() {
  Mcpwm timer;
  HC_SR04 sensor;

  timer.start();
  while (true) {
    ESP_LOGI(TAG, "Everything has been initialized!!!");
    ESP_LOGI(TAG, "Sleeping for 1 sec...");
    vTaskDelay(pdMS_TO_TICKS(1000));
    ESP_LOGI(TAG, "Woke up");
  }
}

extern "C" void app_main(void) { run_main(); }