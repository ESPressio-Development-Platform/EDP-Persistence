# Memory and Ownership

## Purpose

EDP-Persistence is designed for constrained systems and does not own transfer memory. The contract keeps storage semantics independent from allocation policy.

## Caller-owned transfer memory

`SourceBufferView` and `DestinationBufferView` are non-owning address-and-extent descriptors. The caller allocates and owns the referenced memory before an operation begins and remains responsible for its lifetime.

Persistence does not allocate, resize, free, or retain those ranges. A provider may access them only during the synchronous operation.

A zero-length source or zero-capacity destination may use a null address. For a non-zero extent, the caller must provide a valid accessible range. Raw memory accessibility is a caller precondition rather than a storage failure result.

## Address and enumeration views

`FilePathView` and `KeyView` reference caller-owned validated UTF-8. Modifying their backing bytes invalidates the assumptions established by validation.

Enumeration reuses a caller-provided destination buffer. `TextView` in an enumeration entry references that buffer and is valid only for the callback observation. Consumers that need a name/key later must copy it into memory they own.

## Determinism

The abstract contract performs no per-operation dynamic allocation and requires no heap-owned transfer type. Concrete providers may require bounded/configured scratch storage, but that storage is a provider implementation concern and must obey the applicable EDP memory policies.

## Lifetime and provider ownership

Composition selects provider types; it does not own runtime provider objects. Bootstrap/application wiring owns provider construction, preparation, backing-resource binding, and lifetime.

Consumers hold stable non-owning references/pointers to provider objects. Provider lifetime must dominate all such consumers. Runtime rebinding is outside the abstract contract.
