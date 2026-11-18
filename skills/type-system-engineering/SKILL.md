---
name: type-system-engineering
description: Evolve Goscript type metadata, type syntax, compatibility rules, or static and runtime type checks.
---

# Type system engineering for Goscript

Use this skill when changing type representation, type annotations, compatibility/equality, inference, optional or union types, or type diagnostics.

## Current design

Goscript is described and implemented as dynamically typed at runtime. Type-related syntax is parsed into the AST, and `src/lexer/type_system.c` provides `TypeInfo` constructors, equality, and printing. Treat this as type metadata and supporting logic until call sites demonstrate a static checker or runtime enforcement. Inspect `src/ast/ast.h` for the actual type representation and search all consumers before changing it.

## Workflow

- Establish the requested guarantee: syntax acceptance, metadata preservation, static rejection, runtime validation, or editor support. Do not silently turn a dynamic behavior into a static restriction.
- Trace a type through lexer/parser, AST, type helpers, interpreter, bytecode/VM, and diagnostics as applicable.
- Define compatibility semantics explicitly for primitives, arrays, structs, functions, optionals, unions, and `any`; preserve symmetry and recursive behavior where intended.
- Check incomplete or null type fields and ownership/lifetime when adding recursive type nodes. Keep constructors and comparison/printing logic in sync with new kinds.
- Use focused examples for valid and invalid cases, including nested and boundary cases. Update documentation only for user-visible semantic changes.

Do not infer that Goscript has a full static type checker from the presence of `type_system.c` or `TypeInfo`. Verify the actual enforcement path before claiming a type rule is enforced.
