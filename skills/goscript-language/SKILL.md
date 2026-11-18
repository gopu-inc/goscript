---
name: goscript-language
description: Explain Goscript syntax and runtime behavior, or change the language while keeping its lexer, parser, AST, interpreter, and VM consistent.
---

# Goscript language engineering

Use this skill for questions or changes involving Goscript syntax, semantics,
modules, runtime behavior, or compilation. The repository is the source of truth:
confirm behavior in `src/lexer/scanner.l`, `src/parser/parser.y`, `src/ast/`,
`src/interpreter/`, `src/bytecode/`, and `src/vm/` before documenting support.

## Repository execution paths

- `gd file.gjs` uses the tree-walking interpreter.
- `gd --bytecode file.gjs` uses `src/bytecode/bytecode.c`. This is a separate
  AST bytecode engine and currently falls back to interpreter evaluation for
  constructs it does not lower.
- `src/vm/vm.c` is a separate NaN-boxed stack VM. Do not claim a language
  construct is supported there until both `vm_compile` and `vm_run` implement
  it. Check [backend-status.md](references/backend-status.md).
- `gbc` and `gld` are early package/launcher drivers. GBC includes source and a
  bytecode listing; the ELF object launches `gd`. Neither is standalone native
  compilation.

## Workflow

1. Read [language-reference.md](references/language-reference.md) for the
   lexer/parser surface and known syntax conventions.
2. Trace the feature across tokenization, grammar action, AST ownership,
   interpreter semantics, bytecode lowering, and VM dispatch.
3. Keep the normal interpreter behavior stable. Add explicit compile errors
   when a backend cannot lower a construct; silent `HALT`, no-op opcodes, or
   hidden interpreter fallbacks are not evidence of backend support.
4. Preserve AST ownership rules and keep generated root `scanner.c`, `parser.c`,
   and `parser.h` synchronized through `make` when grammar sources change.
5. Describe partial support precisely. Goscript is dynamically evaluated and
   type annotations do not imply static type checking.

## Syntax changes

The parser uses braces for ordinary blocks and compact keywords such as `lt`,
`cn`, and `ret` (with aliases documented in the reference). For Python-style
`with`, the current accepted form is `with expression as name: statement`; it
does not imply indentation-sensitive suites or a general context-manager
protocol. `open(path)` currently yields the complete file contents as a string
and closes the OS file before the body runs.

## Backend changes

Treat the tree-walking evaluator, `src/bytecode`, and `src/vm` as distinct
engines. Before adding opcodes, verify operand encoding, stack effects, branch
offset conventions, value representation, disassembly, runtime errors, and
every execution path. Read [backend-status.md](references/backend-status.md)
for current gaps and ownership boundaries.
