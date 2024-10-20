idf_component_register(SRCS "HC_SR04.cpp"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES esp_driver_gpio esp_driver_mcpwm)