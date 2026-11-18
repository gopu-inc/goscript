golem greetings

pub const HELLO = "Hello"
pub const WORLD = "World"
pub const WELCOME = "Welcome to Goscript"

pub fn say_hello(name: string) {
    println("Hello, " + name + "!")
}

pub fn say_goodbye(name: string) {
    println("Goodbye, " + name + "!")
}

pub fn get_greeting(name: string): string {
    ret "Hello " + name + "!"
}
