// test_real.gjs - Avec une vraie API
fn fetch_user(id: int): string {
    if id <= 0 {
        raise "Invalid user ID!"
    }
    
    try {
        lt url = f"https://httpbin.org/get?id={id}"
        lt response = await f"curl -s '{url}'"
        ret response
    } catch (e) {
        raise f"API error: {e}"
    }
}

fn main() {
    try {
        lt user = fetch_user(42)
        println(user)
    } except (e) {
        println(f"Failed: {e}")
    } finally {
        println("Done!")
    }
}
