# EDP-Persistence

EDP-Persistence defines the platform-neutral opaque-byte persistence contracts for the ESPressio Development Platform.

It deliberately contains no filesystem, NVS, Preferences, SD, LittleFS, SPIFFS, database, or in-memory implementation. Concrete providers belong in separate EDP-Persistence-* repositories.

## Capabilities

Persistence exposes two independent shared Composition capabilities:

- `FileStorage` — provider-relative opaque files, with optional hierarchy and file mutations.
- `KeyValueStorage` — provider-relative flat keys containing opaque byte values.

A provider may offer either capability or both.

## Core rules

- Callers own every source and destination buffer.
- Persistence never allocates, resizes, releases, or retains caller buffers.
- Successful reads copy as much as the supplied destination can hold and report truncation as a fact.
- Successful mutations commit the complete requested logical mutation.
- Retention, failure preservation, interruption atomicity, concurrency, limits, and optional operation support are compile-time Properties.
- Unsupported optional operations are structurally absent.
- Readiness is observational; lifecycle and concrete configuration belong to Bootstrap/provider owners.
- No serialization, configuration, security, OTA, or application-data semantics are owned by this library.
- Persistence APIs are not promised to be ISR-safe. Keep Persistence work outside ISR context.

## Addressing

`FilePathView` and `KeyView` are validated, non-owning UTF-8 semantic views. Validation is allocation-free and provider-independent.

File paths are canonical provider-relative paths: no leading/trailing separator, empty segments, dot/parent segments, backslash, embedded NUL, or invalid UTF-8. Keys are flat UTF-8 identifiers; characters such as `/` and `.` have no special Persistence meaning.

`DirectoryPathView::Root()` represents provider root without overloading an empty file path.

## Composition

Providers advertise `FileStorage` and/or `KeyValueStorage` Offers through EDP-System Composition.

Use `ValidatePersistenceProvider<T>()` for focused compile-time diagnostics. `FileStorageProvider` and `KeyValueStorageProvider` are available for generic constraints.

The optional open-ended `StorageType` Attribute may describe backing technology, but carries no semantic guarantee.

## Documentation

- [Abstract contract](./docs/CONTRACT.MD) — capability operations, commit/failure semantics, concurrency, capacity, and provider validation.
- [Memory and ownership](./docs/MEMORY_AND_OWNERSHIP.MD) — deterministic caller-owned transfer model and lifetime rules.
- [Composition and providers](./docs/COMPOSITION_AND_PROVIDERS.MD) — Properties, optional structural operations, provider topology, and validation.
- [Results and enumeration](./docs/RESULTS_AND_ENUMERATION.MD) — result invariants, fact masks, truncation, and enumeration behaviour.
- [Build baseline](./docs/BUILDING.MD) — C++20, PIOArduino recommendation, and PlatformIO configuration.
- [Demos](./demos/README.MD) — buildable contract-consumption demonstrations for the policy-required targets.

## Dependencies

- EDP-Persistence
  - EDP-System

There are no optional EDP dependencies in the abstract contract. Concrete providers may introduce their own dependencies in their respective repositories; those are not dependencies of EDP-Persistence.

See [DEPENDENCY_GRAPH.MD](./DEPENDENCY_GRAPH.MD) for the repository dependency graph.

## Tests

`tests/PersistenceContractTests.cpp` contains positive contract, validation, result/fact, arithmetic, and constexpr address tests.

`tests/compile_fail/` contains provider declarations that are required to fail compilation for invalid compile-time contracts. They intentionally do not depend on compiler-specific diagnostic prose.

## Build baseline

EDP-Persistence requires C++20. New Arduino consumers should prefer PIOArduino. Developers retaining conventional PlatformIO must select an Arduino-ESP32 release/toolchain capable of compiling C++20 and explicitly configure the project for `-std=gnu++20`. See [Build baseline](./docs/BUILDING.MD) for details.
