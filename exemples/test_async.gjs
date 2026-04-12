// test_async.gjs
async fn get_user() {
   lt cmd = "whoami"
   lt result = await cmd
   ret result
}

fn main() {
   lt user = await get_user()   // ← AJOUTER await
   println("User: " + user)
}
