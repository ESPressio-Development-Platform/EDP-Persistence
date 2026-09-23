# src/persistence/detail/FileStorageProviderTraits.hpp

**Primary classification:** PRIVATE IMPLEMENTATION

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/detail/FileStorageProviderTraits.hpp)

## Direct includes

- `concepts`
- `type_traits`
- `../FileStorageContract.hpp`
- `PersistencePropertyValidation.hpp`

## Documented declarations

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactMandatoryFileStorageOperations =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactDirectoryMutationOperations =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactRenameOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactAppendOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactWriteFileAtOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactFileCapacityOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    consteval void ValidateFileStorageProvider()
```

