---
name: llvm-codegen-engineering
description: Implement or maintain an LLVM backend for Goscript, including IR lowering, ABI decisions, and LLVM integration.
---

# LLVM code generation engineering

Use this skill only for requests involving LLVM IR generation, LLVM backend design, or an existing LLVM integration.

## Establish the repository state

The current Goscript tree contains a C interpreter and bytecode/VM code (`src/bytecode/`, `src/vm/`) and does not show an LLVM backend in the build or source map. Before editing, verify current files, dependencies, build targets, and the user's intended scope. If the task is to add LLVM support, define the integration boundary and build/dependency approach in the implementation; do not pretend the bytecode VM is LLVM.

## Engineering guidance

- Specify the supported language subset and value representation before lowering. Goscript's dynamic values, closures, imports, FFI, async behavior, and runtime services may require runtime calls or may be outside an initial backend subset.
- Keep AST semantics as the source of truth; distinguish language semantics from LLVM implementation details.
- Make ownership and lifetime of LLVM contexts, modules, builders, and generated artifacts explicit. Preserve diagnostics that identify the source construct being lowered.
- Verify generated IR and execute representative programs through the intended toolchain when asked to validate. Include both successful lowering and clear errors for unsupported constructs.
- Update build instructions and dependency detection only as required for the requested backend, and avoid imposing LLVM on users of existing interpreter/VM paths unless explicitly intended.
