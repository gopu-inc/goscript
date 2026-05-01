// lib/system.gjs
import fs
import db
import ui
import time

module system

lt CONFIG_FILE = "system.conf"
lt LOG_FILE = "activity.log"

pub fn init(app_name: string) {
    ui::clear()
    ui::banner(app_name + " BOOTING...")
    
    log("INFO", "Application " + app_name + " started.")
    
    if (fs::exists(CONFIG_FILE) == "False") {
        log("WARN", "Config missing. Creating default...")
        db::set(CONFIG_FILE, "boot_count", "0")
        db::set(CONFIG_FILE, "last_user", "none")
    }

    lt count = db::get(CONFIG_FILE, "boot_count")
    lt new_count = sysf("echo $((" + count + " + 1))")
    db::set(CONFIG_FILE, "boot_count", new_count)
}

pub fn log(level: string, message: string) {
    lt timestamp = time::now()
    lt entry = "[" + timestamp + "] [" + level + "] " + message
    
    fs::append(LOG_FILE, entry)
    
    if (level == "ERROR") { println(ui::red(entry)) }
    if (level == "WARN")  { println(ui::yellow(entry)) }
    if (level == "INFO")  { println(ui::green(entry)) }
}

pub fn get_param(key: string): string {
    ret db::get(CONFIG_FILE, key)
}

