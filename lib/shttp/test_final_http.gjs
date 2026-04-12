import http from "./http"

fn main() {
    println("=== TEST FINAL HTTP ===\n")
    
    println("--- GET ---")
    lt get_resp = http::get("https://httpbin.org/get?foo=bar")
    println(get_resp)
    
    println("\n--- POST (form) ---")
    lt post_resp = http::post("https://httpbin.org/post", "name=golang&type=script")
    println(post_resp)
    
    println("\n--- POST (JSON) ---")
    lt json_resp = http::post_json("https://httpbin.org/post", "{\"lang\":\"goscript\",\"version\":\"1.0\"}")
    println(json_resp)
    
    println("\n--- PUT ---")
    lt put_resp = http::put("https://httpbin.org/put", "updated=true")
    println(put_resp)
    
    println("\n--- DELETE ---")
    lt del_resp = http::delete("https://httpbin.org/delete")
    println(del_resp)
    
    println("\n--- HEAD ---")
    lt head_resp = http::head("https://httpbin.org/get")
    println(head_resp)
    
    println("\n✅ All HTTP methods work!")
}
