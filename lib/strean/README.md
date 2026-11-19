# Strean

Strean is a small Flask-style HTTP framework for Goscript. Import the package
with `import strean`. The package is a singleton application: register routes
in `main`, then call `strean::run(port)`.

`run` listens on loopback for local development. Use
`strean::run_on("0.0.0.0", port)` when the app should accept connections from
other machines.

```gjs
import strean

fn home(request: any): any {
    ret strean::html("<h1>Hello</h1>")
}

fn user(request: any): any {
    ret strean::json("{\"name\":\"" + strean::param(request, "name") + "\"}")
}

fn page_one(request: any): any {
    with open("index.html", "r") as page {
        ret strean::html(page)
    }
}

fn main() {
    strean::get("/", home)
    strean::get("/users/:name", user)
    strean::route("GET", "/page", page_one)
    strean::run(8080)
}
```

`with` and `whith` accept either a braced block or the older one-statement
colon form. `open(path, "r")` reads and closes the file, then exposes its
contents as a string in the block.

## Package modules

- `request.gjs`: HTTP request parsing, path/query/header/body/form/cookie access.
- `response.gjs`: text, HTML, JSON text, status, redirect, custom headers, and wire formatting.
- `router.gjs`: GET, POST, PUT, PATCH, DELETE and OPTIONS routes, plus `:name` path parameters.
- `middleware.gjs`: ordered before-request callbacks, a logger, and optional CORS response headers.
- `static.gjs`: read a text file and return it with an extension-based MIME type.
- `template.gjs`: replace `{{key}}` placeholders from a string dictionary.
- `config.gjs`: process-local key/value configuration.
- `json.gjs`: JSON string escaping and string-field helpers.
- `__self__.gjs`: package facade and server entry point.

Handlers receive a request dictionary with `method`, `path`, `query`, `headers`,
`body`, `params`, and `raw`. A handler may return a string (text response) or a
response made by `strean::text`, `strean::html`, `strean::json`, `strean::status`,
or `strean::redirect`. `strean::json` takes an already serialized JSON string;
`strean::json_quote` and `strean::json_string_field` help create string fields.

Goscript's current runtime is single-threaded for this server path. Requests are
handled sequentially, one per TCP connection. URL decoding, chunked request
bodies, sessions, and automatic JSON serialization are not implemented yet.
Templates support string substitutions only. The framework uses the runtime's
native TCP support and needs the normal Goscript build dependencies.

## Compiler

`make` builds `gd`, `gbc`, and `gld`. `gbc app.gjs -o app.gbc` creates a GBC
package, and `gld app.gbc -o app.o` emits an ELF launcher object. Link it with
`cc app.o -o app`, then run `./app`.

This pipeline is an early runtime-backed implementation: GBC carries source
plus a bytecode listing, and the ELF object launches `gd` to execute the source.
It is not yet standalone native code. The separate `vm_compile()` backend is
still incomplete, so `--bytecode` uses the AST bytecode engine, which falls
back to the interpreter for language features it has not lowered yet.
