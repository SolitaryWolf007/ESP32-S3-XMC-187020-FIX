// SPDX-FileCopyrightText: 2026 Project contributors
// SPDX-License-Identifier: Apache-2.0

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("BOOT OK: Arduino com bootloader XMC 20 70 18");
  Serial.printf("Arduino-ESP32: %s\n", ESP_ARDUINO_VERSION_STR);
  Serial.printf("ESP-IDF: %s\n", ESP.getSdkVersion());
  Serial.printf("Flash: %u bytes (%u MiB)\n",
                ESP.getFlashChipSize(), ESP.getFlashChipSize() / (1024U * 1024U));
  Serial.printf("PSRAM encontrada: %s\n", psramFound() ? "sim" : "nao (isolada)");
}

void loop() {
  static uint32_t seconds = 0;
  Serial.printf("uptime=%lu s\n", static_cast<unsigned long>(seconds));
  delay(5000);
  seconds += 5;
}
