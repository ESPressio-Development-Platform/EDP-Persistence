# src/persistence/KeyValueStorageContract.hpp

**Primary classification:** INTERNAL PROVIDER API

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/KeyValueStorageContract.hpp)

## Direct includes

- `concepts`
- `PersistenceComposition.hpp`
- `PersistenceTypes.hpp`
- `PersistenceViews.hpp`

## Documented declarations

### `KeyEnumerationEntry`

**Classification:** INTERNAL PROVIDER API

One KeyValueStorage enumeration observation.

```cpp
struct KeyEnumerationEntry final
```

### `Key`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Key text backed by the caller's reusable key buffer.

```cpp
TextView Key;
```

### `CompleteKeySize`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Complete UTF-8 key size before destination truncation.

```cpp
StorageSize CompleteKeySize;
```

### `ValueSize`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Current complete logical value size.

```cpp
StorageSize ValueSize;
```

### `Facts`

**Classification:** INTERNAL PROVIDER API · source access: `public`

One-byte mask containing KeyEnumerationEntryFact values.

```cpp
std::uint8_t Facts;
```

### `TCallback`

**Classification:** INTERNAL PROVIDER API

Callback accepted by KeyValueStorage key enumeration.
TCallback is the caller-owned callback type being constrained.

```cpp
template<class TCallback>
    concept KeyEnumerationCallback = requires(
        TCallback& Callback,
        const KeyEnumerationEntry& Entry
    )
```

### `KeyEnumerationCallbackProbe`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Constructs a callback probe used only for compile-time provider validation.

```cpp
KeyEnumerationCallbackProbe() = default;
```

### `operator`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Accepts one KeyValueStorage enumeration entry during compile-time expression checking.

```cpp
[[nodiscard]] EnumerationControl operator()(const KeyEnumerationEntry&) noexcept
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasMandatoryKeyValueStorageOperations = requires(
            TProvider& MutableProvider,
            const TProvider& Provider,
            KeyView Key,
            DestinationBufferView Destination,
            SourceBufferView Source
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasKeyEnumerationOperation = requires(
            const TProvider& Provider,
            DestinationBufferView KeyBuffer,
            KeyEnumerationCallbackProbe& Callback
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasReadValueAtOperation = requires(
            const TProvider& Provider,
            KeyView Key,
            StorageOffset Offset,
            DestinationBufferView Destination
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasClearAllOperation = requires(TProvider& Provider)
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasKeyValueCapacityOperation = requires(const TProvider& Provider)
```

