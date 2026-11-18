# Goscript language reference from the implementation

This is an implementation map, not a claim that every token has complete
runtime semantics. The lexer is `src/lexer/scanner.l`; grammar productions
and AST construction are in `src/parser/parser.y`.

## Source conventions

- Functions: `fn name(args) { ... }`, public functions: `pub fn name(...)`.
- Mutable declarations: `lt name = value` or `let name = value`; immutable
  declarations: `cn name = value`; mutable-state declarations also use
  `muts name = value`.
- Return: `ret value` or `return value`.
- Blocks use `{ ... }`; statement lists are parsed without indentation rules.
- Function parameters may have a type annotation and default value. Return
  annotations use the grammar's `return_type` production; inspect that rule
  before changing its exact spelling.
- `with expr as name: statement` binds a resource value for one statement.
  Current `open(path)` returns the file contents as a string and closes the
  file immediately; this is not a general `__enter__`/`__exit__` protocol.

## Expressions and declarations

Implemented grammar families include numeric, string, boolean and `nil`
literals; unary and binary operations; calls; member and static access; arrays;
dictionaries (`dict`/`map` tokens also appear in type/declaration syntax);
indexing; struct initialization with `new`; lambdas; ternary expressions;
f-strings; ranges; pipe expressions; `await`, `spawn`, and async forms. The AST
node list in `src/ast/ast.h` is the quickest inventory. Some token families are
currently unused or only partially implemented.

Control-flow grammar includes `if`/`else`, `for`, `while`, `loop`, `break`,
`continue`, `match`/`switch`, and `try`/`catch`/`finally`/`throw`. `except` and
`raise` are lexer tokens; token presence alone does not establish parser
support. Check each production in `parser.y`.

Type and aggregate grammar includes type annotations, optional types, arrays,
dictionaries, structs, enums, `impl`, inheritance-shaped struct extensions,
patterns, and constraints. The runtime is dynamic; do not infer static
checking from annotation syntax.

## Modules and declarations

The lexer and parser include `import`, `export`, `use`, `golem <name>`, `packet`, and
decorator syntax. Module resolution and evaluation are implemented in
`src/interpreter/interpreter_import.c`. Module aliases and package `__self__.gjs`
resolution matter to examples; inspect the loader before changing path rules.

## Operators

The grammar declares assignment and compound-assignment, boolean `||`/`&&`,
equality, ordering, arithmetic, unary negation/not, bitwise operators, ranges,
optional/coalescing tokens, and pipe-forward syntax. Precedence is defined in
the precedence declarations near the start of `parser.y`; runtime support may
differ by operator and backend.

## Built-ins and host access

Many standard operations are exposed through Goscript libraries or C/FFI
registration in `src/interpreter/`. `sysf` captures shell output and `sh`
executes shell commands. Native C calls, network functions, and module loading
are interpreter facilities unless an alternate backend implements them.
Prefer the focused library API over undocumented native names.

## Where to verify a claim

Search the token in `scanner.l`, its production in `parser.y`, constructor and
destructor cases in `ast.c`, the evaluator switch in `interpreter_eval.c`, and
both compiler and dispatch switches in backend sources. A missing switch case
usually means partial semantics, not a parser error.
