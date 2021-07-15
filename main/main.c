#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "math.h"
#include "esp_log.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

#define SPEED_MODE_0    ((pow(2.0, 13.0) - 1) * 0.0)
#define SPEED_MODE_80    ((pow(2.0, 13.0) - 1) * 0.8)
#define SPEED_MODE_90    ((pow(2.0, 13.0) - 1) * 0.9)
#define SPEED_MODE_100      (8191)


static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
            .speed_mode       = LEDC_MODE,
            .timer_num        = LEDC_TIMER,
            .duty_resolution  = LEDC_DUTY_RES,
            .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
            .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
            .speed_mode     = LEDC_MODE,
            .channel        = LEDC_CHANNEL,
            .timer_sel      = LEDC_TIMER,
            .intr_type      = LEDC_INTR_DISABLE,
            .gpio_num       = LEDC_OUTPUT_IO,
            .duty           = 0, // Set duty to 0%
            .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void switch_speed_mode() {
    int speed;

    while(1) {
        printf("What speed you want? \n"
               "0 = 0%%\n"
               "1 = 80%%\n"
               "2 = 90%%\n"
               "3 = 100%%\n");
        scanf("%d", &speed);

        switch (speed) {
            case 0:
                ESP_LOGI("APP", "0%% Speed");
                // Set duty to 0%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_0));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            case 1:
                ESP_LOGI("APP", "80%% Speed");
                // Set duty to 80%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_80));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            case 2:
                ESP_LOGI("APP", "90%% Speed");
                // Set duty to 90%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_90));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            case 3:
                ESP_LOGI("APP", "100%% Speed");
                // Set duty to 100%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_100));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            default:
                ESP_LOGI("APP", "50%% Speed");
                // Set duty to 50%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
        }

        vTaskDelay(400 / portTICK_RATE_MS);
    }
}

void app_main(void)
{
    // Set the LEDC peripheral config
    example_ledc_init();
    // Create Task to control speed
    TaskHandle_t xHandle = NULL;
    xTaskCreate(switch_speed_mode, "SPEED", 4095, NULL, 5, xHandle);
}
