# Build, Test and Source Map

C++20 is required. `docs/` covers the contract, Composition/providers, ownership, result/enumeration semantics and building. Tests should validate provider concept conformance, impossible property combinations, optional-operation structural presence and result normalization.

Arduino IDE / Arduino CLI validation must exercise the repository as an installed/local Arduino library through `library.properties` and the root `ESPressio_Persistence.hpp` include, not through manually injected `src` paths.
