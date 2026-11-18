---
name: runtime-vm-engineering
description: Debug or extend Goscript runtime evaluation, bytecode execution, VM values, garbage collection, or native calls.
---

# Runtime and VM engineering for Goscript

Use this skill for runtime semantics, interpreter evaluation, bytecode, VM instruction execution, value representation, garbage collection, and runtime/native boundaries.

## Repository map

- Interpreter code is under `src/interpreter/`.
- An AST-oriented bytecode layer is under `src/bytecode/`.
- A separate stack VM and its instruction definitions are under `src/vm/`; runtime objects and collection are under `src/gc/`.
- FFI and platform integration live under `src/ffi/` and `src/hal/`.

These components may not be interchangeable or equally complete. Trace the command-line execution path and feature implementation before choosing a target.

## Workflow

- Define the user-visible semantic contract first, then locate its interpreter, bytecode, and VM implementations. Keep behavior aligned where multiple paths are supported.
- For opcodes, update the enum/encoding, emitter or compiler, dispatch implementation, stack effects, control flow, and debug/dump support together. Check operand bounds and instruction pointer behavior.
- For value representation or GC changes, audit every encode/decode and object access path, roots on stacks/frames/globals, allocation thresholds, and cleanup. Preserve pointer/tag assumptions used by NaN boxing.
- For calls and native boundaries, verify argument order/count, return value, errors, and ownership of strings/objects. Respect FFI sandboxing and existing runtime checks.
- Cover edge cases such as nil, truthiness, numeric conversions, nested calls, exceptions, and collection during allocation when they relate to the change.

Do not report a runtime feature as supported based only on opcode declarations or headers; confirm that code generation and execution paths implement it.
