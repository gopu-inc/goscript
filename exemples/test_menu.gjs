import ui
import os
import net

fn main() {
    println(ui::blue("option: 1 = network"))     
    println(ui::blue("option: 2 = list dir"))    
    println(ui::blue("option: 3 = system info")) 
    println(ui::blue("option: 4 = exiting... "))
    lt choice = ui::menu("GOSCRIPT CONTROL CENTER", "Check Network,List Files,System Info,Exit")
     
    if (choice == "1") {
        println(ui::blue("\nChecking Network..."))
        println("Status: " + net::ping("8.8.8.8"))
    }
    
    if (choice == "2") {
        println(ui::blue("\nCurrent Directory Content:"))
        println(os::list_dir("."))
    }

    if (choice == "3") {
        println(ui::blue("\nSystem Information:"))
        println("User: " + os::getenv("USER"))
        println("Path: " + os::getcwd())
    }

    if (choice == "4") {
        println(ui::red("Exiting..."))
    }

    ret 0
}

