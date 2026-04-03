import Class

struct User {
    base: Class::BaseObject,
    username: string,
    role: string
}

impl User {
    pub fn __new(name, role) {
        return new User {
            base: Class::create("User"),
            username: name,
            role: role
        }
    }

    pub fn say_hello(self) {
        print("Hello, I am ")
        print(self.username)
        print(" (")
        self.base::inspect()
        println(")")
    }
}

fn main() {
    let admin = User::__new("Alexis", "Admin")
    admin::say_hello()
    
    // Concaténation de string (ton interpréteur gère l'opérateur +)
    println("Created at: " + admin.base.created_at)
}
