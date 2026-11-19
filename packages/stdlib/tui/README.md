# tui

Terminal UI components for Goscript, inspired by Rich:

- `heading`, `rule`, `panel`, `table`
- `progress`, `progress_bar`
- `markdown`
- `prompt`, `confirm`
- `status`
- ANSI colors and 24-bit RGB
- terminal width, cursor, and clearing helpers

```goscript
import .lib.tui as tui

println(tui::heading("Golem", "Package registry"))
println(tui::panel("Status", "All services are available"))
println(tui::table("Name|Version|Status", "openv|0.1.1|ready\nbase|0.1.0|ready"))
println(tui::progress(72, "Downloading"))
```
