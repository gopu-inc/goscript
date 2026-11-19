import fs
import db
import ui
import time

golem system

lt CONFIG_FILE = "system.conf"
lt LOG_FILE = "activity.log"

pub fn init(app_name: string) {
    ui::clear()
    ui::banner(app_name + " BOOTING...")
    log("INFO", "Application " + app_name + " started.")
    if fs::exists(CONFIG_FILE) == false {
        log("WARN", "Config missing. Creating default...")
        db::set(CONFIG_FILE, "boot_count", "0")
        db::set(CONFIG_FILE, "last_user", "none")
    }
    lt count = db::get(CONFIG_FILE, "boot_count")
    db::set(CONFIG_FILE, "boot_count", str(atoi_c(count) + 1))
}

pub fn log(level: string, message: string) {
    lt timestamp = time::now()
    lt entry = "[" + timestamp + "] [" + level + "] " + message + "\n"
    fs::append(LOG_FILE, entry)
    if level == "ERROR" { println(ui::red(entry)) }
    if level == "WARN" { println(ui::yellow(entry)) }
    if level == "INFO" { println(ui::green(entry)) }
}

pub fn get_param(key: string): string { ret db::get(CONFIG_FILE, key) }
