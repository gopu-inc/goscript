# builbase

`builbase` is a small Goscript package with consistent console helpers for build scripts.

## Install

Add the package to the `[dependencies]` section of `Manifest.toml`:

```toml
[dependencies]
builbase = "0.1.1"
```

Then run:

```sh
golem install
```

## Use

```goscript
import builbase

fn main() {
    builbase::banner("Release")
    builbase::step("Compiling sources")
    if (builbase::require(true, "Compilation failed")) {
        builbase::success("Compilation complete")
    }
}
```

The package exports `version`, `banner`, `step`, `success`, `error`, and `require`.
`require` prints an error message and returns `false` when its condition is false.

## License

MIT. See `LICENSE`.
