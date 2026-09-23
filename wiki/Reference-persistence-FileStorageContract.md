# src/persistence/FileStorageContract.hpp

**Primary classification:** INTERNAL PROVIDER API

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/FileStorageContract.hpp)

## Direct includes

- `concepts`
- `PersistenceComposition.hpp`
- `PersistenceTypes.hpp`
- `PersistenceViews.hpp`

## Documented declarations

### `FileEnumerationEntry`

**Classification:** INTERNAL PROVIDER API

One FileStorage directory-enumeration observation.

```cpp
struct FileEnumerationEntry final
```

### `Name`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Entry name backed by the caller's reusable name buffer.

```cpp
TextView Name;
```

### `CompleteNameSize`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Complete UTF-8 entry-name size before destination truncation.

```cpp
StorageSize CompleteNameSize;
```

### `FileSize`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Logical file size when FileSizeIsKnown is set, otherwise zero.

```cpp
StorageSize FileSize;
```

### `Facts`

**Classification:** INTERNAL PROVIDER API · source access: `public`

One-byte mask containing FileEnumerationEntryFact values.

```cpp
std::uint8_t Facts;
```

### `Kind`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Kind of FileStorage entry being delivered.

```cpp
FileEntryKind Kind;
```

### `TCallback`

**Classification:** INTERNAL PROVIDER API

Callback accepted by FileStorage directory enumeration.
TCallback is the caller-owned callback type being constrained.

```cpp
template<class TCallback>
    concept FileEnumerationCallback = requires(
        TCallback& Callback,
        const FileEnumerationEntry& Entry
    )
```

### `FileEnumerationCallbackProbe`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Constructs a callback probe used only for compile-time provider validation.

```cpp
FileEnumerationCallbackProbe() = default;
```

### `operator`

**Classification:** INTERNAL PROVIDER API · source access: `public`

Accepts one FileStorage enumeration entry during compile-time expression checking.

```cpp
[[nodiscard]] EnumerationControl operator()(const FileEnumerationEntry&) noexcept
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasMandatoryFileStorageOperations = requires(
            TProvider& MutableProvider,
            const TProvider& Provider,
            FilePathView Path,
            StorageOffset Offset,
            DestinationBufferView Destination,
            SourceBufferView Source
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasDirectoryMutationOperations = requires(
            TProvider& Provider,
            FilePathView Path
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasDirectoryEnumerationOperation = requires(
            const TProvider& Provider,
            DirectoryPathView Directory,
            DestinationBufferView NameBuffer,
            FileEnumerationCallbackProbe& Callback
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasRenameOperation = requires(
            TProvider& Provider,
            FilePathView Source,
            FilePathView Destination
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasAppendOperation = requires(
            TProvider& Provider,
            FilePathView Path,
            SourceBufferView Source
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasWriteFileAtOperation = requires(
            TProvider& Provider,
            FilePathView Path,
            StorageOffset Offset,
            SourceBufferView Source
        )
```

### `TProvider`

**Classification:** INTERNAL PROVIDER API

TProvider is the provider type whose operation surface is being inspected.

```cpp
template<class TProvider>
        concept HasFileCapacityOperation = requires(const TProvider& Provider)
```

