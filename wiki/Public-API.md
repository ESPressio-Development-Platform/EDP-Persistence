# Public API

FileStorage mandatory operations cover readiness, size, ranged read, whole-file replacement and removal. Optional operations include directory management/enumeration, rename, append, ranged writes and capacity reporting.

KeyValueStorage mandatory operations cover readiness, value size, read, store and remove. Optional operations include enumeration, ranged read, clear-all and capacity.

Public property vocabulary describes access mode, retention, hierarchy, case sensitivity, removability, size/path limits, invocation concurrency, optional-operation support, failure preservation and interruption atomicity. `FilePathView` and `KeyView` are validated non-owning UTF-8 views.

Exact declarations remain authoritative in the exported headers.
