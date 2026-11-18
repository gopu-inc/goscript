// Start with ./gd test_strean.gjs, then try:
// curl -i http://127.0.0.1:19391/
// curl -i http://127.0.0.1:19391/hello/Goscript?from=curl
// curl -i -X POST -d 'name=Goscript' http://127.0.0.1:19391/echo
// curl -i http://127.0.0.1:19391/page
import strean

fn home(request: any): any {
    lt result = strean::html("<h1>" + strean::config_get("APP_NAME") + " is running</h1>")
    result = strean::header(result, "X-Framework", "strean")
    ret strean::cookie(result, "session", "demo")
}

fn greeting(request: any): any {
    lt name = strean::param(request, "name")
    lt source = strean::query(request, "from")
    ret strean::json("{\"hello\":" + strean::json_quote(name) + ",\"from\":" + strean::json_quote(source) + "}")
}

fn echo_form(request: any): any {
    lt fields = strean::form(request)
    ret strean::text("received: " + fields["name"])
}

fn rendered_page(request: any): any {
    lt values = {}
    values["name"] = strean::param(request, "name")
    ret strean::html(strean::render("<h1>Hello {{name}}</h1>", values))
}

fn main() {
    strean::config_set("APP_NAME", "Strean")
    strean::before_request(strean::logger)
    strean::enable_cors()
    strean::get("/", home)
    strean::get("/hello/:name", greeting)
    strean::post("/echo", echo_form)
    strean::get("/template/:name", rendered_page)
    with open("index.html") as page: strean::route("GET", "/page", page)
    strean::run(19391)
}
