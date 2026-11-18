---
name: language-server-engineering
description: Build or extend editor language services for Goscript, including diagnostics, completion, navigation, and semantic tokens.
---

# Language server engineering for Goscript

Use this skill for Language Server Protocol (LSP) servers and editor services such as diagnostics, completion, hover, navigation, formatting, and semantic tokens.

## Establish the starting point

The repository includes editor integration such as `grammars/`, `syntaxes/`, `vim/`, `language-configuration.json`, and `package.json`; these provide syntax/editor support but do not by themselves constitute an LSP server. Inspect the package scripts, extension sources, and build configuration before deciding whether the request is an enhancement or a new server.

## Engineering guidance

- Reuse the language's actual lexical and grammar rules where practical, or document the limits of any separate parser used for editor features. Avoid diagnostics that disagree with the compiler on common syntax.
- Keep document text and derived parse state scoped to the open document URI. Handle incremental/full text changes and close notifications without stale diagnostics or cross-file state leakage.
- Make features resilient to incomplete source while users type; avoid crashing or flooding diagnostics on partial syntax.
- Convert source offsets and ranges carefully, respecting the negotiated LSP position encoding and the editor's line/character conventions.
- Keep server protocol output separate from logs and diagnostics on stdout. Advertise only capabilities the server actually handles and respond correctly to cancellation and shutdown.
- Add protocol-level or editor integration coverage for lifecycle, edits, malformed/incomplete files, and representative Goscript constructs when verification is requested.

If no server exists, treat implementing one as a new component: keep its dependency and launch configuration explicit and coordinate syntax behavior with the existing compiler and editor grammars.
