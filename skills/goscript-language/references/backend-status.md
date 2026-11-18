# Compiler and runtime backend map

## Three distinct execution engines

### Tree-walking interpreter

`src/main.c` parses a program and calls `interpret_program`. The evaluator and
module loader are under `src/interpreter/`. This is the broadest execution
path and currently owns most native functions and library integration.

### AST bytecode engine (`--bytecode`)

`src/bytecode/bytecode.c` has its own `BCOpCode`, compiler, stack, and runner.
Supported expressions are lowered to instructions; unsupported nodes can emit
`BC_EVAL_EXPR` or `BC_EVAL_STMT`, which call back into the tree interpreter.
The `.gbc` container stores original source and a textual bytecode listing;
loading it reparses source. Therefore it is not a serialized executable chunk.

### Stack VM (`src/vm`)

`src/vm/vm.h` declares NaN-boxed values, a broad opcode enum, chunks, frames,
and upvalue structures. `src/vm/vm.c` has partial dispatch, TODO handlers,
placeholder globals/collections/calls, and an AST compiler that historically
emitted only `HALT`. Audit each opcode's compiler and runtime implementation
before relying on it. `vm_execute` is not the CLI's `--bytecode` path.

## GBC and native launcher path

`gd --emit-gbc` writes a `GBC1` header followed by source and the textual dump
from `bc_program_dump`. Loading a `.gbc` file reads its source, parses it, and
selects the AST bytecode engine. `gd --emit-native-gbc` emits a relocatable C
launcher object that embeds source and starts the `gd` runtime. It needs a C
link driver and the runtime executable at execution time; it is not native code
generation from Goscript semantics.

The `gbc` and `gld` aliases select those modes by executable name. Keep their
documentation explicit about these limitations until a stable bytecode file
format, VM lowering, and standalone runtime are implemented.

## Invariants when extending the VM

- Keep the NaN-box tags, pointer-width assumptions, and truthiness rules
  consistent across encode/decode and every opcode.
- For each emitted opcode, document stack inputs/outputs and operand meaning.
- Jump operands are interpreted relative to the current instruction in the
  threaded dispatch; patch calculations must match this convention.
- Validate constant-pool indexes, local slots, stack capacity, frame depth,
  and opcode bounds before dispatch.
- Keep the threaded and fallback-switch dispatch paths equivalent.
- A feature is supported only when AST lowering, both dispatch paths, error
  behavior, and observable output agree; declarations or opcode names alone
  are insufficient.

## Tensor and neural-network C library

`src/tensor.h` defines the public CPU tensor API and `src/tensor.c` implements
the naive CPU kernels. Goscript modules `lib/tensor.gjs` and `lib/nn.gjs` expose
handle-based 2D tensor operations and single-dense-layer training. `src/nn.h`
and `src/nn.c` implement the C layer, MSE optimizer, numeric-column text/JSONL
loader, and model serialization. The JSONL reader extracts the first requested
numeric values from each line; it is not schema-aware JSON. Training is full
batch gradient descent for one dense layer. Tensor autograd covers basic
elementwise operations, selected activations, reductions, and matrix multiply;
extended shape ops, CNN kernels, NPY, CUDA, Metal, and accelerated backends
remain incomplete. Do not describe this as a complete general-purpose deep
learning framework.
