import proc from "./proc"

fn main() {
    println("=== TEST PROC ===\n")
    println("My PID: " + proc::my_pid())
    println("PPID: " + proc::ppid())
}
