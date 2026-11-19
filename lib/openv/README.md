# OpenV

OpenV stores simple `KEY=value` entries in a `.openv` file in the current
working directory. It does not modify the parent process environment.

## Install

Add OpenV and its filesystem dependency to `Manifest.toml`:

```toml
[dependencies]
openv = "0.1.1"
fs = "0.1.0"
```

Then run `golem install`.

## Use

```goscript
import openv

fn main() {
    openv::set("API_URL", "https://example.test/v1")
    println(openv::get("API_URL"))
}
```

`openv::add` fails if the key already exists. `openv::set` inserts a missing
key or replaces its existing value. Values may contain `=`; keys cannot contain
`=` or line breaks.
