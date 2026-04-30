import config

fn main() {
    // On cherche l'URL de l'API
    lt conf_api = config::parser_conf("/etc/gpm.conf", "API_URL")
    println("API URL -> " + conf_api.parse)
    
    // On cherche le répertoire d'installation
    lt conf_dir = config::parser_conf("/etc/gpm.conf", "INSTALL_DIR")
    println("Install Dir -> " + conf_dir.parse)
}

