# EDP-Persistence Abstract Contract

## Scope

EDP-Persistence owns addressable opaque-byte persistence semantics. It does not own encoding, serialization, encryption, configuration, OTA policy, application schemas, filesystem mounting, media formatting, or concrete storage technology.

## FileStorage

Mandatory operations:

- `IsFileStorageReady() const noexcept`
- `GetFileSize(FilePathView) const noexcept`
- `ReadFileAt(FilePathView, StorageOffset, DestinationBufferView) const noexcept`
- `ReplaceFile(FilePathView, SourceBufferView) noexcept`
- `RemoveFile(FilePathView) noexcept`

Optional compile-time operations:

- `CreateDirectory` and `RemoveDirectory`
- `EnumerateDirectory`
- `RenameEntry`
- `AppendFile`
- `WriteFileAt`
- `GetFileStorageCapacity`

Optional methods are present exactly when the corresponding Support Property is Supported.

Read-only providers retain the mandatory mutation methods so the capability remains substitutable; those methods return ReadOnly. Optional mutation support must be Unsupported.

## KeyValueStorage

Mandatory operations:

- `IsKeyValueStorageReady() const noexcept`
- `GetValueSize(KeyView) const noexcept`
- `ReadValue(KeyView, DestinationBufferView) const noexcept`
- `StoreValue(KeyView, SourceBufferView) noexcept`
- `RemoveKey(KeyView) noexcept`

Optional compile-time operations:

- `EnumerateKeys`
- `ReadValueAt`
- `ClearAllKeys`
- `GetKeyValueStorageCapacity`

A zero-length value is a present value and is distinct from an absent key.

## Read results

`ReadResult<TStatus>` contains:

- primary status;
- one-byte fact mask;
- bytes transferred into the caller's destination;
- `AvailableDataSize`.

`AvailableDataSize` is the complete number of logical bytes available to that particular read request before destination capacity is applied. For ranged reads this means bytes remaining from the requested offset.

Whole-value reads always know available size. Ranged providers need not perform otherwise unnecessary metadata I/O solely to discover it.

On read failure:

- `Facts == None`;
- `BytesTransferred == 0`;
- `AvailableDataSize == 0`.

Any internal destination-buffer touches before failure are not semantically consumable.

## Enumeration

Enumeration is one synchronous non-mutating operation. The caller supplies one reusable destination buffer for each delivered name/key.

Callbacks:

- are compile-time typed;
- are invoked by lvalue reference;
- are `noexcept`;
- return `EnumerationControl::Continue` or `EnumerationControl::Stop`;
- must perform bounded work;
- must not recursively invoke Persistence within the same coordination domain.

`EntriesVisited` counts callback invocations. It remains truthful when a later operational failure ends enumeration. The callback that returns Stop is included.

UTF-8 names and keys are truncated only at code-point boundaries. Complete encoded size remains available even when the destination capacity is zero.

## Commit, retention and failure

A successful state-changing operation means the complete requested logical mutation has crossed the provider commit boundary sufficiently to satisfy its advertised retention.

`RetentionLevel` is ordered:

`Session < Restart < PowerLoss`.

Returned mutation failure is characterized separately by `FailurePreservation`.

Abrupt interruption is characterized by `InterruptionAtomicity`, ordered:

`None < Restart < PowerLoss`.

An interruption guarantee cannot exceed the provider's retention guarantee.

## Concurrency

`InvocationConcurrency` is ordered:

`CallerSerialized < ConcurrentReads < ConcurrentOperations`.

The Property describes safe invocation, not physical parallel execution. A provider may internally serialize.

`ConcurrentOperations` requires each operation to be linearizable. Providers sharing interfering backing state must share sufficient coordination for the advertised guarantee to remain true.

## Capacity

Capacity reporting is optional and observational.

When supported, successful queries return total and currently available capacity for the provider's backing allocation domain, with available capacity no greater than total capacity.

Capacity does not reserve future space and need not change arithmetically by the exact size of a logical mutation.

## Validation and provider contracts

`ValidatePersistenceProvider<T>()` validates every Persistence capability advertised by `T`.

Validation includes:

- mandatory Property presence;
- conditional Property presence;
- read-only consistency;
- hierarchy consistency;
- optional method structural presence;
- exact fixed-operation signatures, constness and noexcept;
- mutation guarantee presence;
- retention/atomicity compatibility;
- address-size constraints;
- callback compatibility.

Provider runtime construction, ownership, preparation, teardown, and backing-resource binding are deliberately outside this abstract contract.
