# EDP-Persistence Demos

The abstract library has no concrete storage backend, so its buildable demo demonstrates the public contract facilities that are meaningful without selecting a concrete provider: validated addressing, checked storage arithmetic, fact inspection, and result handling.

The same logical demonstration is supplied for every target required by the ESPressio demo policy:

- `ContractBasics/Arduino_IDE`
- `ContractBasics/PlatformIO_Arduino`
- `ContractBasics/PlatformIO_ESP-IDF`

Each target depends on EDP-System and EDP-Persistence and requires C++20. Platform-specific storage demonstrations belong to the future concrete `EDP-Persistence-*` provider repositories.
