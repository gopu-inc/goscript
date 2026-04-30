import gsql.db

fn main() {
    lt my_db = db::open("data.db", 30)
    lt res = db::query(my_db, "SELECT * FROM users;")
    println(res)
    db::close(my_db)
}

