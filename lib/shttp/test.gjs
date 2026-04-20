import websocket as wc


lt connect = wc::serve(8080, "echo 'hello'")
println(connect)
