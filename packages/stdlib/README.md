# Goscript standard packages

This directory contains the buildable Golem package projects for the standard
library modules shipped with Goscript. Each package has its own `Manifest.toml`
and produces an archive under its `build/` directory.

Build the full set from the repository root with:

```sh
make standard-packages
```

The package set is `b64`, `config`, `crypto`, `db`, `error`, `fmt`, `fs`,
`gcsv`, `gsql`, `http`, `httplib`, `io`, `json`, `math`, `net`, `nn`, `os`,
`random`, `s256`, `sqlite`, `std`, `strings`, `tar`, `tensor`, `time`, `ui`,
`urllib`, and `xzip`. The OpenV add-on also depends on `fs`.

The same command also builds the existing `openv` add-on project in
`lib/openv/`.

The package sources call the Goscript runtime's native APIs for filesystem,
time, random, strings, compression, SQLite, and networking operations. Package
sources do not use `sysf`, `sh`, or shell command strings. Some adapters such as
HTTP, hashing, and tar still invoke their system utility through argv from the
runtime layer; they do not pass a command through a shell.
