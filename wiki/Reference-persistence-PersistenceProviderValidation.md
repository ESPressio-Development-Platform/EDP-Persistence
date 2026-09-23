# src/persistence/PersistenceProviderValidation.hpp

**Primary classification:** INTERNAL PROVIDER API

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/PersistenceProviderValidation.hpp)

## Direct includes

- `type_traits`
- `detail/FileStorageProviderTraits.hpp`
- `detail/KeyValueStorageProviderTraits.hpp`

## Documented declarations

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
        concept PersistenceProviderDeclaration = requires
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
        [[nodiscard]] consteval bool IsFileStorageProviderContractValid()
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
        [[nodiscard]] consteval bool IsKeyValueStorageProviderContractValid()
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

Validates every Persistence capability advertised by one provider with focused diagnostics.
TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    consteval void ValidatePersistenceProvider()
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

Constrains a type to the complete FileStorage provider contract.
TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept FileStorageProvider =
        Detail::IsFileStorageProviderContractValid<TProvider>();
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

Constrains a type to the complete KeyValueStorage provider contract.
TProvider is the provider type being constrained or validated.

```cpp
template<class TProvider>
    concept KeyValueStorageProvider =
        Detail::IsKeyValueStorageProviderContractValid<TProvider>();
```

