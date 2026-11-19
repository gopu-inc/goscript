# fs

`fs` provides native file and directory helpers for Goscript: `read`, `write`,
`append`, `size`, `exists`, `mkdir`, and `remove`. These functions call the
Goscript runtime API directly and do not construct shell commands.

## Install

```toml
[dependencies]
fs = "0.2.0"
```

Then run `golem install`.

## Use

```goscript
import fs

fn main() {
    fs::write("notes.txt", "first line\n")
    fs::append("notes.txt", "second line\n")
    println(fs::read("notes.txt"))
}
```

