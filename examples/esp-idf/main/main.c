// SPDX-FileCopyrightText: 2026 Project contributors
// SPDX-License-Identifier: Apache-2.0

#include <inttypes.h>
#include <stdio.h>

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_idf_version.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "xmc_test";

void app_main(void)
{
    esp_chip_info_t chip_info;
    uint32_t flash_size = 0;
    esp_chip_info(&chip_info);
    ESP_ERROR_CHECK(esp_flash_get_size(NULL, &flash_size));

    ESP_LOGI(TAG, "ESP-IDF: %s", esp_get_idf_version());
    ESP_LOGI(TAG, "chip: ESP32-S3 rev %d.%d, cores=%d",
             chip_info.revision / 100, chip_info.revision % 100, chip_info.cores);
    ESP_LOGI(TAG, "flash detectada: %" PRIu32 " bytes (%" PRIu32 " MiB)",
             flash_size, flash_size / (1024 * 1024));
    ESP_LOGI(TAG, "PSRAM isolada nesta compilacao; heap SPIRAM=%u bytes",
             (unsigned)heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
    ESP_LOGI(TAG, "BOOT OK: teste XMC 20 70 18 em execucao");

    uint32_t seconds = 0;
    while (true) {
        ESP_LOGI(TAG, "uptime=%" PRIu32 " s", seconds);
        vTaskDelay(pdMS_TO_TICKS(5000));
        seconds += 5;
    }
}
