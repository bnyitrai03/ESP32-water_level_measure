#include "esp_http_client.h"
#include "esp_log.h"
#include "firebase_api.h"

#define FIREBASE_HOST "your-database-name.firebaseio.com"  // Firebase host
#define FIREBASE_PATH "/your-data-path.json"
static const char *TAG = "firebase";

esp_err_t firebase_post(const char *data) {
    esp_http_client_config_t config = {
        .host = FIREBASE_HOST,
        .path = FIREBASE_PATH,
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, data, strlen(data));
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "POST Status = %d", esp_http_client_get_status_code(client));
    } else {
        ESP_LOGE(TAG, "POST failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
    return err;
}

esp_err_t firebase_get() {
    esp_http_client_config_t config = {
        .host = FIREBASE_HOST,
        .path = FIREBASE_PATH,
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "GET Status = %d", esp_http_client_get_status_code(client));
    } else {
        ESP_LOGE(TAG, "GET failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
    return err;
}