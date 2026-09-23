# src/persistence/detail/PersistencePropertyValidation.hpp

**Primary classification:** PRIVATE IMPLEMENTATION

**Source baseline:** `a943780a2c90d07669eeaff4313ad7161d1e9b04`

[Open exact source](https://github.com/ESPressio-Development-Platform/EDP-Persistence/blob/a943780a2c90d07669eeaff4313ad7161d1e9b04/src/persistence/detail/PersistencePropertyValidation.hpp)

## Direct includes

- `cstdint`
- `type_traits`
- `../PersistenceComposition.hpp`

## Documented declarations

### `TProperties`

**Classification:** PRIVATE IMPLEMENTATION

TProperties is the provider Property set; TProperty is the Property being inspected.

```cpp
template<class TProperties, class TProperty>
    inline constexpr bool HasPropertyV = TProperties::template Contains<TProperty>;
```

### `TProperties`

**Classification:** PRIVATE IMPLEMENTATION

TProperties is the provider Property set; TProperty is the Property being inspected.

```cpp
template<class TProperties, class TProperty>
    consteval auto PropertyValue()
```

### `TProperties`

**Classification:** PRIVATE IMPLEMENTATION

TProperties is the provider Property set; the remaining template types identify the optional-operation support and guarantee Properties.

```cpp
template<
        class TProperties,
```

