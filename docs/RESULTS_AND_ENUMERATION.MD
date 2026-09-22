# Results and Enumeration

## Result model

Fallible Persistence operations return dedicated strongly typed status enums or structured result types. Boolean returns are reserved for predicates such as readiness.

A structured result never leaves a failure payload semantically ambiguous. Unless explicitly stated otherwise, fields that are meaningful only on success are normalized to zero on failure.

## Read results

`ReadResult<TStatus>` contains a primary status, one-byte fact mask, transferred byte count, and `AvailableDataSize`.

On success, `BytesTransferred` is meaningful. `AvailableDataSize` is meaningful when `ReadFact::AvailableDataSizeIsKnown` is set. When known, truncation and smaller-than-buffer facts describe the relationship between complete available data and destination capacity; exact fit sets neither relationship bit.

On non-success, Facts is None, BytesTransferred is zero, and AvailableDataSize is zero. No partially touched destination prefix is semantically consumable.

Consumers should inspect facts with `HasFact` and ignore future fact bits they do not understand.

## Size and capacity

A successful size query returns the complete logical size, including zero. Failure normalizes Size to zero.

A successful capacity query returns total and available capacity with available no greater than total. Failure normalizes both values to zero. Capacity is observational and does not reserve future space.

## Enumeration

Enumeration is synchronous, incremental, and allocation-free at the contract boundary. The caller supplies reusable storage for the delivered name/key and a compile-time typed `noexcept` callback.

`EntriesVisited` always reports the number of callbacks actually invoked, including the callback that returns Stop. It therefore remains meaningful after a later operational failure.

File entries report kind, complete name size, and optional file size. Directory entries never advertise a file size and normalize FileSize to zero. Key entries always report current ValueSize.

Name/key truncation occurs only at UTF-8 code-point boundaries. Complete encoded size is reported independently of the populated prefix, so zero-capacity metadata-only enumeration is valid.

Callbacks must perform bounded work and must not recursively invoke Persistence in the same coordination domain while the enumeration operation is active.
