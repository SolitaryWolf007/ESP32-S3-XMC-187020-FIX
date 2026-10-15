# ESP32-S3 boot fix for XMC flash `0x187020`

[Versão em português](README.pt-BR.md)

Minimal, reproducible fix for ESP32-S3 N16R8 boards stuck in a reset loop with an XMC flash identified as manufacturer `0x20`, device `0x7018`, JEDEC ID `0x187020`.

The problem was reproduced with ESP-IDF 5.5.5 and matches [espressif/esp-idf#18947](https://github.com/espressif/esp-idf/issues/18947). The bootloader recognizes the XMC vendor but its strict validation does not accept MFID `0x70`. The patch adds `0x70` to the same capacity range already accepted for `0x41`.

This repository includes the one-line patch, a reproducible ESP-IDF test project, a prebuilt bootloader, and an Arduino sketch that automatically uses the fixed bootloader.

## Verified setup

- ESP32-S3 revision 0.2, N16R8;
- XMC 16 MB flash, ID `20 70 18`, quad 3.3 V;
- Arduino-ESP32 3.3.12 / ESP-IDF 5.5.5;
- DIO mode, 40 MHz bootloader image header;
- PSRAM disabled in the test firmware.

The board successfully left the reset loop and ran the test sketch after flashing.

## Arduino IDE

Open [`examples/arduino/XMCBootTest/XMCBootTest.ino`](examples/arduino/XMCBootTest/XMCBootTest.ino), select **ESP32S3 Dev Module**, then use **16MB**, **DIO**, **PSRAM Disabled**, and **115200 baud**. Keep full-flash erase disabled.

Arduino-ESP32 automatically prefers a file named `bootloader.bin` in the sketch directory. To use the fix in another sketch, copy [`prebuilt/bootloader.bin`](prebuilt/bootloader.bin) next to its `.ino` file. Do not replace files in the global `Arduino15` installation.

## Rebuild

Apply [`patches/esp-idf-v5.5.5-xmc-mfid-0x70.patch`](patches/esp-idf-v5.5.5-xmc-mfid-0x70.patch) to the complete [ESP-IDF v5.5.5](https://github.com/espressif/esp-idf/releases/tag/v5.5.5) tree and build the project under `examples/esp-idf`. See the [Portuguese README](README.pt-BR.md) for the exact commands.

Prebuilt binary SHA-256:

```text
F37CF7872A0CE2A9B1DA847EA79A5FFAEF8961CBA48CD99F493ACB117F470BF4
```

This is a community fix validated on the hardware listed above, not an official Espressif fix. Back up important flash contents first, and do not use the prebuilt image with Secure Boot or Flash Encryption without reviewing the original configuration.

## License

Original repository code and the modification are made available under the Apache License 2.0. The prebuilt bootloader contains components derived from ESP-IDF, Newlib, and the GCC runtime under their respective licenses and exceptions. See [`NOTICE`](NOTICE), [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md), and [`licenses/`](licenses/).
