#include "HC_SR04.h"
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"

static const char *TAG = "HC_SR04";

class mcpwm {
private:
  mcpwm_cap_timer_handle_t _timer;
  mcpwm_capture_timer_config_t _timer_config;

public:
  mcpwm() {
    _timer_config.clk_src = MCPWM_CAPTURE_CLK_SRC_DEFAULT;
    _timer_config.group_id = 0;

    ESP_ERROR_CHECK(mcpwm_new_capture_timer(&_timer_config, &_timer));
    ESP_LOGI(TAG, "Capture timer registered");
  }
};

class HC_SR04 {
private:
  static void gen_trig_output(void);

public:
  HC_SR04() {}
};