# Compile-fail contract tests

Each translation unit in this directory is intentionally invalid and must fail compilation when compiled as C++20 against EDP-Persistence and EDP-System.

The fixtures cover representative provider-author errors:

- a read-only FileStorage Offer advertising mutation support;
- hierarchical FileStorage omitting MaximumPathSegmentBytes;
- an optional method being present while its Support Property is Unsupported;
- a mandatory mutation method with incorrect constness.

The tests deliberately assert only that compilation fails. They do not depend on compiler-specific diagnostic wording.
