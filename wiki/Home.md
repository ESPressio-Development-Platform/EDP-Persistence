# EDP-Persistence Developer Wiki

EDP-Persistence defines SDK-neutral opaque-byte persistence contracts for file-style and key/value storage without owning concrete filesystem or NVS implementations.

This Wiki is maintained beside the code on `main`. Source code and repository `docs/` remain normative; the Wiki is the internal developer explanation/navigation layer and must evolve with code changes.

## Public entry point

```cpp
#include <ESPressio_Persistence.hpp>
```

## Dependencies

Mandatory: EDP-System only.

Use [Architecture](Architecture.md), [Public API](Public-API.md), [Internal API](Internal-API.md), [Implementation](Implementation.md), [Composition](Composition.md), [Resources / Lifecycle / Concurrency](Resources-Lifecycle-Concurrency.md), and [Build / Test / Source](Build-Test-Source.md).

## Arduino packaging

EDP-Persistence carries `library.properties` and exports `ESPressio_Persistence.hpp` as its Arduino root include. This makes the documented Arduino IDE surface discoverable without manual compiler include-path injection.
