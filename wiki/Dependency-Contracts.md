# Dependency Contracts

EDP-Persistence depends only on **EDP-System**.

## EDP-System

The Persistence domain, shared `FileStorage` and `KeyValueStorage` capabilities, and the extensive provider-property vocabulary are expressed through the EDP-System Composition Framework.

## No runtime lower-layer dependency

The abstract persistence contracts own no filesystem, NVS, byte-copy or synchronization implementation. Caller-owned buffers and provider semantics are part of the contract; concrete API implementations live in provider repositories.

## FileStorage provider contract

A conforming provider must advertise the FileStorage capability and its applicable properties: access mode, retention, hierarchy, case sensitivity, removability, size/path limits, optional-operation support, invocation concurrency, failure preservation and interruption atomicity.

Mandatory operations include readiness, size, ranged read, replace and remove. Optional operations are structurally present only when the corresponding Support property is Supported.

## KeyValueStorage provider contract

A conforming provider advertises key/value access/retention/case/removability/limits, optional-operation support, invocation concurrency, failure preservation and interruption atomicity, and implements the mandatory readiness/size/read/store/remove surface.

## Consumer qualification

Higher repositories may place constraints directly on these properties. EDP-Localisation FilePackSource, for example, requires FileStorage ConcurrentReads and a sufficient MaximumPathBytes value.

## Internal provider API

Provider validation traits under Persistence Detail namespaces are internal implementation/provider APIs. Concrete Persistence provider repositories must continue to satisfy them even though applications should normally consume the public concepts/contracts.

> Dependency contract audit baseline: `d4586e6a2e4d68a35210be88c6ce23ab62135101` (`main`).
