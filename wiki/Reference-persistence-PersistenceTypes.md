# src/persistence/PersistenceTypes.hpp

**Primary classification:** PUBLIC API

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/PersistenceTypes.hpp)

## Direct includes

- `cstddef`
- `cstdint`

## Documented declarations

### `StorageSize`

**Classification:** PUBLIC API

Represents a logical persisted-data size.

```cpp
struct StorageSize final
```

### `RawValue`

**Classification:** PUBLIC API · source access: `public`

Underlying 64-bit storage size.

```cpp
std::uint64_t RawValue;
```

### `StorageSize`

**Classification:** PUBLIC API · source access: `public`

Constructs a zero storage size.

```cpp
constexpr StorageSize() noexcept : RawValue(0U) {}
```

### `StorageSize`

**Classification:** PUBLIC API · source access: `public`

Constructs a storage size from its underlying value.

```cpp
explicit constexpr StorageSize(std::uint64_t Value) noexcept : RawValue(Value) {}
```

### `operator`

**Classification:** PUBLIC API · source access: `public`

Compares two storage sizes for equality.

```cpp
friend constexpr bool operator==(StorageSize, StorageSize) noexcept = default;
```

### `Left`

**Classification:** PUBLIC API · source access: `public`

Orders two storage sizes by their underlying byte counts.

```cpp
[[nodiscard]] friend constexpr bool operator<(StorageSize Left, StorageSize Right) noexcept
```

### `Left`

**Classification:** PUBLIC API · source access: `public`

Determines whether the left storage size does not exceed the right.

```cpp
[[nodiscard]] friend constexpr bool operator<=(StorageSize Left, StorageSize Right) noexcept
```

### `Left`

**Classification:** PUBLIC API · source access: `public`

Determines whether the left storage size exceeds the right.

```cpp
[[nodiscard]] friend constexpr bool operator>(StorageSize Left, StorageSize Right) noexcept
```

### `Left`

**Classification:** PUBLIC API · source access: `public`

Determines whether the left storage size is at least the right.

```cpp
[[nodiscard]] friend constexpr bool operator>=(StorageSize Left, StorageSize Right) noexcept
```

### `StorageOffset`

**Classification:** PUBLIC API

Represents an offset within logical persisted data.

```cpp
struct StorageOffset final
```

### `RawValue`

**Classification:** PUBLIC API · source access: `public`

Underlying 64-bit storage offset.

```cpp
std::uint64_t RawValue;
```

### `StorageOffset`

**Classification:** PUBLIC API · source access: `public`

Constructs a zero storage offset.

```cpp
constexpr StorageOffset() noexcept : RawValue(0U) {}
```

### `StorageOffset`

**Classification:** PUBLIC API · source access: `public`

Constructs a storage offset from its underlying value.

```cpp
explicit constexpr StorageOffset(std::uint64_t Value) noexcept : RawValue(Value) {}
```

### `operator`

**Classification:** PUBLIC API · source access: `public`

Compares two storage offsets for equality.

```cpp
friend constexpr bool operator==(StorageOffset, StorageOffset) noexcept = default;
```

### `CheckedStorageSizeResult`

**Classification:** PUBLIC API

Result of checked storage-size arithmetic.

```cpp
struct CheckedStorageSizeResult final
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Outcome of the checked arithmetic operation.

```cpp
StorageArithmeticStatus Status;
```

### `Value`

**Classification:** PUBLIC API · source access: `public`

Resulting value, normalized to zero when the operation does not succeed.

```cpp
StorageSize Value;
```

### `CheckedAdd`

**Classification:** PUBLIC API

Adds two storage sizes without permitting unsigned wraparound.

```cpp
[[nodiscard]] constexpr CheckedStorageSizeResult CheckedAdd(
        StorageSize Left,
        StorageSize Right
    ) noexcept
```

### `CheckedStorageOffsetResult`

**Classification:** PUBLIC API

Result of checked storage-offset arithmetic.

```cpp
struct CheckedStorageOffsetResult final
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Outcome of the checked arithmetic operation.

```cpp
StorageArithmeticStatus Status;
```

### `Value`

**Classification:** PUBLIC API · source access: `public`

Resulting value, normalized to zero when the operation does not succeed.

```cpp
StorageOffset Value;
```

### `CheckedAdd`

**Classification:** PUBLIC API

Adds a logical byte extent to an offset without permitting unsigned wraparound.

```cpp
[[nodiscard]] constexpr CheckedStorageOffsetResult CheckedAdd(
        StorageOffset Offset,
        StorageSize Extent
    ) noexcept
```

### `IsOffsetWithinOrAtEnd`

**Classification:** PUBLIC API

Indicates whether an offset identifies a position at or before a logical size.

```cpp
[[nodiscard]] constexpr bool IsOffsetWithinOrAtEnd(
        StorageOffset Offset,
        StorageSize Size
    ) noexcept
```

### `AvailableFromOffset`

**Classification:** PUBLIC API

Returns the bytes available from a previously validated offset.

```cpp
[[nodiscard]] constexpr StorageSize AvailableFromOffset(
        StorageSize Size,
        StorageOffset Offset
    ) noexcept
```

### `SourceBufferView`

**Classification:** PUBLIC API

Describes caller-owned immutable source bytes.

```cpp
struct SourceBufferView final
```

### `Address`

**Classification:** PUBLIC API · source access: `public`

First readable source byte, or null when Size is zero.

```cpp
const void* Address;
```

### `Size`

**Classification:** PUBLIC API · source access: `public`

Number of readable source bytes.

```cpp
std::size_t Size;
```

### `DestinationBufferView`

**Classification:** PUBLIC API

Describes caller-owned writable destination bytes.

```cpp
struct DestinationBufferView final
```

### `Address`

**Classification:** PUBLIC API · source access: `public`

First writable destination byte, or null when Capacity is zero.

```cpp
void* Address;
```

### `Capacity`

**Classification:** PUBLIC API · source access: `public`

Number of writable destination bytes.

```cpp
std::size_t Capacity;
```

### `TFact`

**Classification:** PUBLIC API

Tests one understood fact bit without requiring exact-mask equality.
TFact is the scoped fact enum containing the requested bit.

```cpp
template<class TFact>
    [[nodiscard]] constexpr bool HasFact(std::uint8_t Facts, TFact Fact) noexcept
```

### `TStatus`

**Classification:** PUBLIC API

Read result carrying the capability-specific primary status.
TStatus is the primary status enum for the requested read operation.

```cpp
template<class TStatus>
    struct ReadResult final
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Primary mutually exclusive read outcome.

```cpp
TStatus Status;
```

### `Facts`

**Classification:** PUBLIC API · source access: `public`

One-byte mask containing orthogonal ReadFact values.

```cpp
std::uint8_t Facts;
```

### `BytesTransferred`

**Classification:** PUBLIC API · source access: `public`

Number of bytes semantically transferred on success.

```cpp
std::size_t BytesTransferred;
```

### `AvailableDataSize`

**Classification:** PUBLIC API · source access: `public`

Logical bytes available to this read range when the corresponding fact is set.

```cpp
StorageSize AvailableDataSize;
```

### `TStatus`

**Classification:** PUBLIC API

Size-query result carrying the capability-specific primary status.
TStatus is the primary status enum for the requested size operation.

```cpp
template<class TStatus>
    struct SizeQueryResult final
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Primary mutually exclusive size-query outcome.

```cpp
TStatus Status;
```

### `Size`

**Classification:** PUBLIC API · source access: `public`

Complete logical object size on success, otherwise normalized to zero.

```cpp
StorageSize Size;
```

### `TStatus`

**Classification:** PUBLIC API

Enumeration result carrying the capability-specific primary status.
TStatus is the primary status enum for the requested enumeration operation.

```cpp
template<class TStatus>
    struct EnumerationResult final
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Primary mutually exclusive enumeration outcome.

```cpp
TStatus Status;
```

### `EntriesVisited`

**Classification:** PUBLIC API · source access: `public`

Number of callbacks actually invoked before the operation returned.

```cpp
StorageSize EntriesVisited;
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Primary mutually exclusive capacity-query outcome.

```cpp
CapacityQueryStatus Status;
```

### `TotalCapacity`

**Classification:** PUBLIC API · source access: `public`

Total capacity of the backing allocation domain on success.

```cpp
StorageSize TotalCapacity;
```

### `AvailableCapacity`

**Classification:** PUBLIC API · source access: `public`

Currently available capacity of the backing allocation domain on success.

```cpp
StorageSize AvailableCapacity;
```

