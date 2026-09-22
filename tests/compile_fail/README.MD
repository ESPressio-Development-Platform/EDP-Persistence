# Compile-fail contract tests

Each translation unit in this directory is intentionally invalid and must fail compilation when compiled as C++20 against EDP-Persistence and EDP-System.

The fixtures cover representative provider-author errors:

- a read-only FileStorage Offer advertising mutation support;
- hierarchical FileStorage omitting MaximumPathSegmentBytes;
- an optional method being present while its Support Property is Unsupported;
- a mandatory mutation method with incorrect constness.

The tests deliberately assert only that compilation fails. They do not depend on compiler-specific diagnostic wording.


## Local runner

From the repository root, `python3 tests/run_tests.py` compiles and runs the positive suite, then compiles every `*.cpp` in this directory with `-fsyntax-only` and requires a non-zero compiler result.

The runner uses the real EDP-System checkout by default. Use `--system /path/to/EDP-System` when it is not a sibling repository. `--support-stub` deliberately selects the isolated test shim and therefore does not constitute real EDP-System integration validation.
