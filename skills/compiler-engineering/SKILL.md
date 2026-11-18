---
name: compiler-engineering
description: Design, debug, or extend Goscript compilation pipelines and cross-stage compiler behavior.
---

# Compiler engineering for Goscript

Use this skill for changes spanning multiple compilation stages or for compiler architecture decisions. Goscript is primarily a C implementation with a Flex scanner (`src/lexer/scanner.l`), Bison grammar (`src/parser/parser.y`), AST (`src/ast/`), an interpreter, and bytecode/VM components. The root `Makefile` generates the root `scanner.c`, `parser.c`, and `parser.h`; treat those as generated outputs unless the task specifically targets generated artifacts.

## Workflow

- Trace the feature end to end before editing: source syntax, token, grammar action, AST representation, runtime or bytecode handling, diagnostics, and tests/examples.
- Confirm which execution path the main program uses. This repository contains both an interpreter and VM-related code; do not assume a feature in one path is implemented in the other.
- Keep language behavior consistent across affected paths. For a deliberate divergence, identify it in code or documentation and cover its user-visible consequences.
- Follow existing ownership and error-reporting conventions in the touched C code. Check allocations, cleanup, and failure paths when adding AST or compiler-owned data.
- Prefer changes to source files under `src/`; regenerate parser/scanner outputs through the Makefile only when needed by the project's build process.
- Add or update focused tests and examples that demonstrate accepted syntax, rejected syntax, and runtime behavior where applicable.

## Boundaries

There is no evident LLVM backend in the current source tree. If a request mentions LLVM, first inspect the repository and determine whether the task is to introduce a backend or to modify an existing component; do not describe the existing VM as LLVM code generation. The language has dynamic runtime behavior, so do not assume static compilation or type checking merely from type-related syntax or metadata.
