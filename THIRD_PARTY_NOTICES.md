# Third-party notices

The prebuilt `bootloader.bin` was produced with ESP-IDF v5.5.5 and the Espressif Xtensa toolchain. It contains or may contain code originating from the following projects. These notices are included conservatively; a component appearing here does not imply that every symbol from that component is present in the final binary.

## ESP-IDF

Copyright (c) 2015-2026 Espressif Systems (Shanghai) CO LTD.

The original ESP-IDF source is licensed under the Apache License 2.0, reproduced in [`LICENSE`](LICENSE). ESP-IDF contains additional third-party code; Espressif's copyright and license inventory is reproduced in [`licenses/ESP-IDF-COPYRIGHT.rst`](licenses/ESP-IDF-COPYRIGHT.rst).

Upstream: <https://github.com/espressif/esp-idf/tree/v5.5.5>

Modification: `components/bootloader_support/bootloader_flash/src/bootloader_flash.c` was changed to accept XMC MFID `0x70` in the capacity range already accepted for MFID `0x41`. The complete change is in [`patches/esp-idf-v5.5.5-xmc-mfid-0x70.patch`](patches/esp-idf-v5.5.5-xmc-mfid-0x70.patch).

## Newlib

The bootloader link map includes Newlib C runtime objects. Newlib is a collection of software carrying several permissive copyright notices and licenses. The complete upstream notice distributed with ESP-IDF is reproduced in [`licenses/NEWLIB.txt`](licenses/NEWLIB.txt).

## GCC runtime library

The bootloader link map includes helper objects from `libgcc`. The relevant GNU GPL version 3 text and GCC Runtime Library Exception 3.1 are reproduced in:

- [`licenses/GCC-COPYING3.txt`](licenses/GCC-COPYING3.txt)
- [`licenses/GCC-RUNTIME-LIBRARY-EXCEPTION.txt`](licenses/GCC-RUNTIME-LIBRARY-EXCEPTION.txt)

The runtime exception permits eligible compiled target code to be distributed under terms of the distributor's choice, independently of the GCC license, subject to the exception's conditions.

## micro-ecc

The ESP-IDF bootloader build includes the micro-ecc component in its component graph. Its BSD-2-Clause license is reproduced in [`licenses/MICRO-ECC.txt`](licenses/MICRO-ECC.txt). It is included here conservatively even when link-time removal excludes its symbols from a particular bootloader configuration.

## No endorsement

Names and trademarks belonging to Espressif Systems and other copyright holders are used only for factual identification. They do not imply endorsement of this community modification.
