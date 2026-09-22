# Build Baseline

## C++20

EDP-Persistence requires official C++20. This is required by the EDP-System Composition Framework and is not an optional compatibility mode.

## Arduino development

New Arduino-ESP32 consumers should prefer **PIOArduino** rather than the older PlatformIO Arduino platform packages because the EDP baseline requires a modern Arduino-ESP32/toolchain with C++20 support.

## Conventional PlatformIO

If conventional PlatformIO is retained, the project must deliberately select an Arduino-ESP32 platform/toolchain release that supports C++20 and enable C++20 explicitly.

A project configuration should include the equivalent of:

```ini
build_unflags =
    -std=gnu++11

build_flags =
    -std=gnu++20
```

The exact platform/package pin belongs to the consuming application because EDP-Persistence itself is platform-neutral. The important contract is that the selected Arduino-ESP32/toolchain genuinely supports the C++20 language baseline rather than relying on an older PlatformIO default.

## ESP-IDF

ESP-IDF consumers likewise compile the library as C++20. EDP-Persistence contains no direct ESP-IDF references; concrete integration belongs behind the appropriate EDP Platform/Persistence provider layers.
