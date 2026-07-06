# Goscript

A modern, lightweight scripting language interpreter (`.gjs` files) developed by GOPU inc. Written in C with Flex/Bison for lexing/parsing and libffi for FFI support.

## Build

```bash
make
```

This generates the `gd` binary (the Goscript interpreter).

## Usage

```bash
./gd script.gjs          # Run a script
./gd --version           # Show version
./gd --help              # Show help
```

## Dependencies

System dependencies (installed via Nix): `flex`, `bison`, `libffi`, `pkg-config`, `gcc`, `make`

## Project Structure

- `src/` — Core C implementation (AST, lexer, parser, interpreter, bytecode VM)
- `lib/` — Standard library modules (`.gjs` files)
- `exemples/` — Example scripts
- `gpm/` — Goscript Package Manager
- `genv/` — Goscript Virtual Environment manager
- `grammars/`, `syntaxes/`, `vim/` — Editor integrations

## Workflow

The "Build Goscript" workflow runs `make` and prints the version to verify the build succeeded.

## User Preferences
