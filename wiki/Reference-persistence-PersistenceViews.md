# src/persistence/PersistenceViews.hpp

**Primary classification:** PUBLIC API

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/PersistenceViews.hpp)

## Direct includes

- `cstddef`
- `cstdint`

## Documented declarations

### `Data_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

First byte of trusted UTF-8 text, or null for an empty view.

```cpp
const char* Data_;
```

### `Size_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Number of meaningful UTF-8 bytes in the view.

```cpp
std::size_t Size_;
```

### `TextView`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Constructs trusted text for provider-owned callback publication.

```cpp
constexpr TextView(const char* Data, std::size_t Size) noexcept
            : Data_(Data),
```

### `Detail`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Grants the provider bridge access to trusted TextView construction.

```cpp
friend struct Detail::PersistenceProviderAccess;
```

### `TextView`

**Classification:** PUBLIC API · source access: `public`

Constructs an empty trusted text view.

```cpp
constexpr TextView() noexcept
            : Data_(nullptr),
```

### `Data`

**Classification:** PUBLIC API · source access: `public`

Returns the first referenced text byte.

```cpp
[[nodiscard]] constexpr const char* Data() const noexcept
```

### `Size`

**Classification:** PUBLIC API · source access: `public`

Returns the number of meaningful referenced bytes.

```cpp
[[nodiscard]] constexpr std::size_t Size() const noexcept
```

### `IsEmpty`

**Classification:** PUBLIC API · source access: `public`

Indicates whether the view contains zero meaningful bytes.

```cpp
[[nodiscard]] constexpr bool IsEmpty() const noexcept
```

### `Data_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

First byte of the validated provider-relative path.

```cpp
const char* Data_;
```

### `Size_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Number of UTF-8 bytes in the validated path.

```cpp
std::size_t Size_;
```

### `FilePathView`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Constructs a path after successful provider-independent validation.

```cpp
constexpr FilePathView(const char* Data, std::size_t Size) noexcept
            : Data_(Data),
```

### `DirectoryPathView`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Allows DirectoryPathView to construct the distinguished provider-root representation.

```cpp
friend class DirectoryPathView;
```

### `ValidationResult`

**Classification:** PUBLIC API · source access: `public`

Structured result returned by FilePathView validation.

```cpp
struct ValidationResult;
```

### `Data`

**Classification:** PUBLIC API · source access: `public`

Returns the first referenced text byte.

```cpp
[[nodiscard]] constexpr const char* Data() const noexcept
```

### `Size`

**Classification:** PUBLIC API · source access: `public`

Returns the number of meaningful referenced bytes.

```cpp
[[nodiscard]] constexpr std::size_t Size() const noexcept
```

### `Validate`

**Classification:** PUBLIC API · source access: `public`

Validates a caller-owned UTF-8 byte range as a canonical FileStorage path.

```cpp
[[nodiscard]] static constexpr ValidationResult Validate(
            const char* Data,
            std::size_t Size
        ) noexcept;
```

### `Validate`

**Classification:** PUBLIC API · source access: `public`

TSize is the compile-time array extent including the string terminator.
Validates a null-terminated FileStorage path literal.

```cpp
template<std::size_t TSize>
        [[nodiscard]] static constexpr ValidationResult Validate(const char (&Value)[TSize]) noexcept;
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Outcome of provider-independent FileStorage path validation.

```cpp
FilePathValidationStatus Status;
```

### `Value`

**Classification:** PUBLIC API · source access: `public`

Validated semantic view when IsValuePresent is true.

```cpp
FilePathView Value;
```

### `IsValuePresent`

**Classification:** PUBLIC API · source access: `public`

Indicates whether Value contains a successfully validated path.

```cpp
bool IsValuePresent;
```

### `Data_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

First byte of the validated key.

```cpp
const char* Data_;
```

### `Size_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Number of UTF-8 bytes in the validated key.

```cpp
std::size_t Size_;
```

### `KeyView`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Constructs a key after successful provider-independent validation.

```cpp
constexpr KeyView(const char* Data, std::size_t Size) noexcept
            : Data_(Data),
```

### `ValidationResult`

**Classification:** PUBLIC API · source access: `public`

Structured result returned by KeyView validation.

```cpp
struct ValidationResult;
```

### `Data`

**Classification:** PUBLIC API · source access: `public`

Returns the first referenced text byte.

```cpp
[[nodiscard]] constexpr const char* Data() const noexcept
```

### `Size`

**Classification:** PUBLIC API · source access: `public`

Returns the number of meaningful referenced bytes.

```cpp
[[nodiscard]] constexpr std::size_t Size() const noexcept
```

### `Validate`

**Classification:** PUBLIC API · source access: `public`

Validates a caller-owned UTF-8 byte range as a canonical KeyValueStorage key.

```cpp
[[nodiscard]] static constexpr ValidationResult Validate(
            const char* Data,
            std::size_t Size
        ) noexcept;
```

### `Validate`

**Classification:** PUBLIC API · source access: `public`

TSize is the compile-time array extent including the string terminator.
Validates a null-terminated KeyValueStorage key literal.

```cpp
template<std::size_t TSize>
        [[nodiscard]] static constexpr ValidationResult Validate(const char (&Value)[TSize]) noexcept;
```

### `Status`

**Classification:** PUBLIC API · source access: `public`

Outcome of provider-independent KeyValueStorage key validation.

```cpp
KeyValidationStatus Status;
```

### `Value`

**Classification:** PUBLIC API · source access: `public`

Validated semantic view when IsValuePresent is true.

```cpp
KeyView Value;
```

### `IsValuePresent`

**Classification:** PUBLIC API · source access: `public`

Indicates whether Value contains a successfully validated key.

```cpp
bool IsValuePresent;
```

### `IsRoot_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Indicates that this view identifies provider root rather than a non-root path.

```cpp
bool IsRoot_;
```

### `Path_`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Validated non-root path; ignored when IsRoot_ is true.

```cpp
FilePathView Path_;
```

### `DirectoryPathView`

**Classification:** PRIVATE IMPLEMENTATION · source access: `private`

Constructs either provider root or a validated non-root directory address.

```cpp
constexpr DirectoryPathView(bool IsRoot, FilePathView Path) noexcept
            : IsRoot_(IsRoot),
```

### `Root`

**Classification:** PUBLIC API · source access: `public`

Returns the semantic provider-root directory address.

```cpp
[[nodiscard]] static constexpr DirectoryPathView Root() noexcept
```

### `NonRoot`

**Classification:** PUBLIC API · source access: `public`

Wraps a validated FileStorage path as a non-root directory address.

```cpp
[[nodiscard]] static constexpr DirectoryPathView NonRoot(FilePathView Path) noexcept
```

### `IsRoot`

**Classification:** PUBLIC API · source access: `public`

Indicates whether this address identifies provider root.

```cpp
[[nodiscard]] constexpr bool IsRoot() const noexcept
```

### `Path`

**Classification:** PUBLIC API · source access: `public`

Returns the non-root path; callers use this only when IsRoot() is false.

```cpp
[[nodiscard]] constexpr FilePathView Path() const noexcept
```

### `PersistenceProviderAccess`

**Classification:** PUBLIC API · source access: `public`

Internal bridge used by conforming providers to construct trusted callback text.

```cpp
struct PersistenceProviderAccess final
```

### `MakeTextView`

**Classification:** PUBLIC API · source access: `public`

Constructs trusted callback text from bytes already validated by a provider.

```cpp
[[nodiscard]] static constexpr TextView MakeTextView(
                const char* Data,
                std::size_t Size
            ) noexcept
```

