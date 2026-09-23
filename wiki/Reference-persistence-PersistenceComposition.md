# src/persistence/PersistenceComposition.hpp

**Primary classification:** PUBLIC API

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/PersistenceComposition.hpp)

## Direct includes

- `cstddef`
- `ESPressio_System.hpp`
- `PersistenceTypes.hpp`

## Documented declarations

### `Composition`

**Classification:** PUBLIC API

Short name for the EDP-System compile-time Composition Framework.

```cpp
namespace Composition = ESPressio::System::CompositionFramework;
```

### `Domain`

**Classification:** PUBLIC API

Composition Domain owning all Persistence capabilities and Properties.

```cpp
struct Domain final : Composition::Domain {};
```

### `FileStorage`

**Classification:** PUBLIC API · source access: `public`

Shared capability for provider-relative opaque file storage.

```cpp
struct FileStorage final : Composition::SharedCapability<Domain> {};
```

### `KeyValueStorage`

**Classification:** PUBLIC API · source access: `public`

Shared capability for provider-relative opaque key/value storage.

```cpp
struct KeyValueStorage final : Composition::SharedCapability<Domain> {};
```

### `TCapability`

**Classification:** PUBLIC API · source access: `public`

TCapability identifies the Persistence capability qualified by the Property; TValue is its compile-time value type.

```cpp
template<class TCapability, class TValue>
    struct PersistenceProperty : Composition::Property<TCapability, TValue> {};
```

### `FileAccessMode`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileAccessMode.

```cpp
struct FileAccessMode final : PersistenceProperty<FileStorage, AccessMode> {};
```

### `FileRetention`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileRetention.

```cpp
struct FileRetention final : PersistenceProperty<FileStorage, RetentionLevel> {};
```

### `FileHierarchyMode`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileHierarchyMode.

```cpp
struct FileHierarchyMode final : PersistenceProperty<FileStorage, FileHierarchy> {};
```

### `FilePathCaseSensitivity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FilePathCaseSensitivity.

```cpp
struct FilePathCaseSensitivity final : PersistenceProperty<FileStorage, TextCaseSensitivity> {};
```

### `FileMediaRemovability`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileMediaRemovability.

```cpp
struct FileMediaRemovability final : PersistenceProperty<FileStorage, MediaRemovability> {};
```

### `MaximumPathBytes`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: MaximumPathBytes.

```cpp
struct MaximumPathBytes final : PersistenceProperty<FileStorage, std::size_t> {};
```

### `MaximumPathSegmentBytes`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: MaximumPathSegmentBytes.

```cpp
struct MaximumPathSegmentBytes final : PersistenceProperty<FileStorage, std::size_t> {};
```

### `MaximumFileSize`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: MaximumFileSize.

```cpp
struct MaximumFileSize final : PersistenceProperty<FileStorage, StorageSize> {};
```

### `DirectoryMutationSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: DirectoryMutationSupport.

```cpp
struct DirectoryMutationSupport final : PersistenceProperty<FileStorage, Support> {};
```

### `DirectoryEnumerationSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: DirectoryEnumerationSupport.

```cpp
struct DirectoryEnumerationSupport final : PersistenceProperty<FileStorage, Support> {};
```

### `RenameSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: RenameSupport.

```cpp
struct RenameSupport final : PersistenceProperty<FileStorage, Support> {};
```

### `AppendSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: AppendSupport.

```cpp
struct AppendSupport final : PersistenceProperty<FileStorage, Support> {};
```

### `WriteFileAtSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: WriteFileAtSupport.

```cpp
struct WriteFileAtSupport final : PersistenceProperty<FileStorage, Support> {};
```

### `FileCapacityReportingSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileCapacityReportingSupport.

```cpp
struct FileCapacityReportingSupport final : PersistenceProperty<FileStorage, Support> {};
```

### `FileInvocationConcurrency`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileInvocationConcurrency.

```cpp
struct FileInvocationConcurrency final : PersistenceProperty<FileStorage, InvocationConcurrency> {};
```

### `FileFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileFailurePreservation.

```cpp
struct FileFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
```

### `FileInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: FileInterruptionAtomicity.

```cpp
struct FileInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
```

### `DirectoryMutationFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: DirectoryMutationFailurePreservation.

```cpp
struct DirectoryMutationFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
```

### `DirectoryMutationInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: DirectoryMutationInterruptionAtomicity.

```cpp
struct DirectoryMutationInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
```

### `RenameFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: RenameFailurePreservation.

```cpp
struct RenameFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
```

### `RenameInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: RenameInterruptionAtomicity.

```cpp
struct RenameInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
```

### `AppendFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: AppendFailurePreservation.

```cpp
struct AppendFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
```

### `AppendInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: AppendInterruptionAtomicity.

```cpp
struct AppendInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
```

### `WriteFileAtFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: WriteFileAtFailurePreservation.

```cpp
struct WriteFileAtFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
```

### `WriteFileAtInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: WriteFileAtInterruptionAtomicity.

```cpp
struct WriteFileAtInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
```

### `KeyValueAccessMode`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueAccessMode.

```cpp
struct KeyValueAccessMode final : PersistenceProperty<KeyValueStorage, AccessMode> {};
```

### `KeyValueRetention`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueRetention.

```cpp
struct KeyValueRetention final : PersistenceProperty<KeyValueStorage, RetentionLevel> {};
```

### `KeyCaseSensitivity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyCaseSensitivity.

```cpp
struct KeyCaseSensitivity final : PersistenceProperty<KeyValueStorage, TextCaseSensitivity> {};
```

### `KeyValueMediaRemovability`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueMediaRemovability.

```cpp
struct KeyValueMediaRemovability final : PersistenceProperty<KeyValueStorage, MediaRemovability> {};
```

### `MaximumKeyBytes`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: MaximumKeyBytes.

```cpp
struct MaximumKeyBytes final : PersistenceProperty<KeyValueStorage, std::size_t> {};
```

### `MaximumKeyValueSize`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: MaximumKeyValueSize.

```cpp
struct MaximumKeyValueSize final : PersistenceProperty<KeyValueStorage, StorageSize> {};
```

### `KeyEnumerationSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyEnumerationSupport.

```cpp
struct KeyEnumerationSupport final : PersistenceProperty<KeyValueStorage, Support> {};
```

### `ReadValueAtSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: ReadValueAtSupport.

```cpp
struct ReadValueAtSupport final : PersistenceProperty<KeyValueStorage, Support> {};
```

### `ClearAllSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: ClearAllSupport.

```cpp
struct ClearAllSupport final : PersistenceProperty<KeyValueStorage, Support> {};
```

### `KeyValueCapacityReportingSupport`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueCapacityReportingSupport.

```cpp
struct KeyValueCapacityReportingSupport final : PersistenceProperty<KeyValueStorage, Support> {};
```

### `KeyValueInvocationConcurrency`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueInvocationConcurrency.

```cpp
struct KeyValueInvocationConcurrency final : PersistenceProperty<KeyValueStorage, InvocationConcurrency> {};
```

### `KeyValueFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueFailurePreservation.

```cpp
struct KeyValueFailurePreservation final : PersistenceProperty<KeyValueStorage, FailurePreservation> {};
```

### `KeyValueInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: KeyValueInterruptionAtomicity.

```cpp
struct KeyValueInterruptionAtomicity final : PersistenceProperty<KeyValueStorage, InterruptionAtomicity> {};
```

### `ClearAllFailurePreservation`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: ClearAllFailurePreservation.

```cpp
struct ClearAllFailurePreservation final : PersistenceProperty<KeyValueStorage, FailurePreservation> {};
```

### `ClearAllInterruptionAtomicity`

**Classification:** PUBLIC API · source access: `public`

Compile-time Persistence Property: ClearAllInterruptionAtomicity.

```cpp
struct ClearAllInterruptionAtomicity final : PersistenceProperty<KeyValueStorage, InterruptionAtomicity> {};
```

