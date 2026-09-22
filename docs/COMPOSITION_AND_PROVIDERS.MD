# Composition and Providers

## Purpose

EDP-Persistence uses EDP-System Composition to express storage capability and substitutability entirely at compile time.

## Domain and capabilities

`Persistence::Domain` owns two independent SharedCapabilities:

- `FileStorage`
- `KeyValueStorage`

A provider may offer either or both. There is deliberately no generic storage ancestor.

## Properties

Properties express semantic guarantees needed for substitution: access mode, retention, addressing/case behaviour, removability, maximum sizes, concurrency, optional-operation support, and mutation guarantees.

Optional operations are structural. A method such as `AppendFile`, `ReadValueAt`, or `EnumerateKeys` is present exactly when its Support Property is `Supported`. Consumers needing one of these facilities constrain Composition accordingly rather than probing at runtime.

Read-only capabilities retain mandatory mutation methods to preserve the base capability shape; those operations return the appropriate `ReadOnly` status. Optional mutation Properties must be Unsupported for read-only providers.

## Attributes

Attributes are open-ended compile-time qualifiers. Persistence standardizes `StorageType` only as optional descriptive metadata. Attributes do not imply semantic guarantees and do not replace Properties.

## Provider topology

Composition resolves provider Types. Bootstrap owns runtime objects and wiring. One provider object may satisfy both Persistence capabilities.

If two logical storage bindings must be independently selectable, they require independently distinguishable provider Types/Offers. Persistence has no runtime service locator, provider registry, default provider, or runtime rebinding facility.

## Validation

`ValidatePersistenceProvider<TProvider>()` validates every Persistence capability advertised by a provider. Public `FileStorageProvider` and `KeyValueStorageProvider` concepts support generic constraints without forcing hard diagnostics during ordinary constraint evaluation.

Validation checks mandatory/conditional Properties, Property consistency, exact operation signatures, constness/noexcept, optional structural presence, read-only rules, hierarchy rules, mutation guarantees, and retention/atomicity compatibility.

Provider construction, mounting, opening, formatting, teardown, and native SDK configuration remain outside this abstract contract.
