# EDP-Persistence Dependency Graph

> Revalidated: 2026-09-24 — Arduino and framework-neutral PlatformIO metadata were added for discoverability only; EDP-System remains the sole mandatory ESPressio dependency and no dependency edge changed.


> Revalidated: 2026-09-23 — Composition Framework enhancement migration changes compile-time provider/requirement metadata and validation only; no ESPressio-library dependency edge changed.

```text
EDP-Persistence
└── EDP-System (mandatory)
```

EDP-Persistence has no optional EDP dependencies.

Concrete provider repositories may consume additional EDP facilities such as EDP-Memory or EDP-Platform according to their implementation needs and applicable policy, but those dependencies are not imposed by the abstract EDP-Persistence library.
