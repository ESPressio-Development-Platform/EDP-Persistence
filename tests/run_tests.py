#!/usr/bin/env python3
"""Run the EDP-Persistence local contract test suite.

By default the suite compiles against the real EDP-System repository when it can
be located beside EDP-Persistence. Pass --system <path> to select it explicitly.

Use --support-stub only for isolated contract development when EDP-System is not
available. The stub is deliberately not the default because it cannot validate
integration with the real Composition Framework.
"""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", help="C++ compiler executable; defaults to CXX, c++, g++, then clang++.")
    parser.add_argument("--system", type=Path, help="Path to a local EDP-System checkout.")
    parser.add_argument("--support-stub", action="store_true", help="Use tests/support/ESPressio_System.hpp instead of real EDP-System.")
    parser.add_argument("--keep-build", action="store_true", help="Keep the temporary build directory for inspection.")
    parser.add_argument("--verbose", action="store_true", help="Print every compiler command.")
    return parser.parse_args()


def find_compiler(requested: str | None) -> str:
    candidates = [requested] if requested else [os.environ.get("CXX"), "c++", "g++", "clang++"]

    for candidate in candidates:
        if candidate and shutil.which(candidate):
            return shutil.which(candidate) or candidate

    raise RuntimeError("No C++ compiler found. Install g++/clang++ or pass --compiler.")


def find_system(repo_root: Path, requested: Path | None) -> Path | None:
    candidates = []
    if requested:
        candidates.append(requested)
    candidates.extend([
        repo_root.parent / "EDP-System",
        repo_root.parent / "ESPressio-System",
    ])

    for candidate in candidates:
        header = candidate / "src" / "ESPressio_System.hpp"
        if header.is_file():
            return candidate.resolve()

    return None


def run(command: list[str], verbose: bool, expect_success: bool = True) -> subprocess.CompletedProcess[str]:
    if verbose:
        print("+", " ".join(command))

    result = subprocess.run(command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    if expect_success and result.returncode != 0:
        print(result.stdout, end="")
        print(result.stderr, end="", file=sys.stderr)
        raise RuntimeError(f"Command failed with exit code {result.returncode}")

    return result


def main() -> int:
    args = parse_args()
    repo_root = Path(__file__).resolve().parents[1]
    compiler = find_compiler(args.compiler)
    system_root = None if args.support_stub else find_system(repo_root, args.system)

    if not args.support_stub and system_root is None:
        print(
            "ERROR: real EDP-System was not found.\n"
            "Clone EDP-System beside EDP-Persistence or pass --system /path/to/EDP-System.\n"
            "Use --support-stub only when deliberately testing against the isolated test shim.",
            file=sys.stderr,
        )
        return 2

    include_args = ["-I", str(repo_root / "src")]

    if args.support_stub:
        include_args += ["-I", str(repo_root / "tests" / "support")]
        dependency_description = "tests/support Composition shim"
    else:
        include_args += ["-I", str(system_root / "src")]
        dependency_description = str(system_root)

    common = [
        compiler,
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Werror",
        *include_args,
    ]

    build_context = tempfile.TemporaryDirectory(prefix="edp-persistence-tests-")
    build_dir = Path(build_context.name)

    if args.keep_build:
        build_context.cleanup = lambda: None  # type: ignore[method-assign]

    try:
        print(f"Compiler: {compiler}")
        print(f"EDP-System: {dependency_description}")
        print(f"Build directory: {build_dir}")

        positive_source = repo_root / "tests" / "PersistenceContractTests.cpp"
        positive_binary = build_dir / "PersistenceContractTests"

        print("\n[1/3] Compiling positive contract tests...")
        run([*common, str(positive_source), "-o", str(positive_binary)], args.verbose)

        print("[2/3] Running positive contract tests...")
        run([str(positive_binary)], args.verbose)

        compile_fail_sources = sorted((repo_root / "tests" / "compile_fail").glob("*.cpp"))
        print(f"[3/3] Verifying {len(compile_fail_sources)} compile-fail fixtures...")

        unexpected_successes: list[Path] = []

        for source in compile_fail_sources:
            result = run(
                [*common, "-fsyntax-only", str(source)],
                args.verbose,
                expect_success=False,
            )

            if result.returncode == 0:
                unexpected_successes.append(source)
                print(f"  FAIL {source.name}: unexpectedly compiled")
            else:
                print(f"  PASS {source.name}: compilation failed as required")

        if unexpected_successes:
            print("\nFAILED: compile-fail fixtures unexpectedly accepted:", file=sys.stderr)
            for source in unexpected_successes:
                print(f"  - {source}", file=sys.stderr)
            return 1

        print("\nPASS: positive tests compiled and ran; every compile-fail fixture was rejected.")
        return 0

    except RuntimeError as error:
        print(f"\nFAILED: {error}", file=sys.stderr)
        return 1
    finally:
        if not args.keep_build:
            build_context.cleanup()


if __name__ == "__main__":
    raise SystemExit(main())
