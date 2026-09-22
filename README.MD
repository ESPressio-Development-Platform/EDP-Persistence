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

## Addressing

`FilePathView` and `KeyView` are validated, non-owning UTF-8 semantic views. Validation is allocation-free and provider-independent.

File paths are canonical provider-relative paths:

- no leading or trailing `/`;
- no empty segments;
- no `.` or `..` segments;
- no backslash;
- no embedded NUL.

Keys are flat UTF-8 identifiers. Characters such as `/` and `.` have no special Persistence meaning for keys.

`DirectoryPathView::Root()` represents provider root without overloading an empty file path.

## Composition

Providers advertise `FileStorage` and/or `KeyValueStorage` Offers through EDP-System Composition.

Use `ValidatePersistenceProvider<T>()` to obtain focused compile-time diagnostics for a provider implementation. `FileStorageProvider` and `KeyValueStorageProvider` are available for generic constraints.

The optional open-ended `StorageType` Attribute may describe backing technology, but it carries no semantic guarantee.

## Dependency boundary

EDP-Persistence depends only on EDP-System.

Concrete providers that need byte-copy primitives consume EDP-Memory in their own implementation repository. Platform/SDK facilities remain behind EDP-Platform and its concrete Platform repositories.

## Tests

`tests/PersistenceContractTests.cpp` contains positive contract, validation, and constexpr address tests.

`tests/compile_fail/` contains representative provider declarations that are required to fail compilation. These tests intentionally do not depend on compiler-specific diagnostic text.

## Documentation

See `docs/CONTRACT.MD` for the complete abstract contract and `examples/ProviderContractExample.cpp` for a minimal provider declaration.
