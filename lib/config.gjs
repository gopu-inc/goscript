golem config

struct Parser {
    Info: string,
    parse: string,
    ligne: int,
    returne: string
}

fn parser_conf(file: string, search: string): Parser {
    if file == "" || search == "" {
        ret new Parser {
            Info: "error",
            parse: "0",
            ligne: 0,
            returne: "Error: Missing file or search term"
        }
    }
    lt result = gs_config_find(file, search)
    lt lines = gs_file_line_count(file)
    ret new Parser {
        Info: "Config: " + file,
        parse: result,
        ligne: lines,
        returne: "Success"
    }
}
