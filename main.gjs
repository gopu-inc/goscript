
struct post {
    code: int,
    msg: string
}

fn Post(codes: int, msg: string) {
    if codes == 200 {
        println(msg)
    }
fn error(msg: string) {
    println(msg)
}

fn main() {
    Post(200, "ok")
    error("internale error")   
    
}
