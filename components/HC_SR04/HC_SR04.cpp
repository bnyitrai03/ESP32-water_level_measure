#include "HC_SR04.h"

static const char *TAG = "HC_SR04";

HC_SR04::HC_SR04() {
  gpio_config_t trig_pin;
  trig_pin.mode = GPIO_MODE_OUTPUT;
  trig_pin.pin_bit_mask = 1ULL << HC_SR04_TRIG_GPIO;
  ESP_ERROR_CHECK(gpio_config(&trig_pin));
  ESP_LOGI(TAG, "Configured Trig pin");

  // drive low by default
  ESP_ERROR_CHECK(gpio_set_level(HC_SR04_TRIG_GPIO, 0));
}

void HC_SR04::generate_trig() {
  gpio_set_level(HC_SR04_TRIG_GPIO, 1);
  esp_rom_delay_us(10);
  gpio_set_level(HC_SR04_TRIG_GPIO, 0);
}