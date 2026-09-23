# src/persistence/detail/KeyValueStorageProviderTraits.hpp

**Primary classification:** PRIVATE IMPLEMENTATION

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/detail/KeyValueStorageProviderTraits.hpp)

## Direct includes

- `concepts`
- `type_traits`
- `../KeyValueStorageContract.hpp`
- `PersistencePropertyValidation.hpp`

## Documented declarations

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactMandatoryKeyValueStorageOperations =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactReadValueAtOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactClearAllOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept ExactKeyValueCapacityOperation =
        requires
```

### `TProvider`

**Classification:** PRIVATE IMPLEMENTATION

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    consteval void ValidateKeyValueStorageProvider()
```

