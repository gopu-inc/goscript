golem golem

lt REGISTRY = "https://gsql-badge.onrender.com"
lt MANIFEST = "Manifest.toml"
lt RELEASE = "r0"
lt ARCH = "x86_64"

fn token_path() {
    ret gpm_home() + "/.config/golem/token"
}

fn account_path() {
    ret gpm_home() + "/.config/golem/account"
}

fn token() {
    ret gpm_read_file(token_path()).trim()
}

fn account() {
    ret gpm_read_file(account_path()).trim()
}

fn ensure_dirs() {
    gpm_mkdirs("modules")
    gpm_mkdirs("build")
    gpm_mkdirs(gpm_home() + "/.config/golem")
}

fn is_version_range(value) {
    ret value.contains("^") || value.contains("~") || value.contains(">") || value == "*"
}

fn valid_name(name) {
    if (gpm_valid_component(name) == 0 || name != name.lower() || name.contains("@")) {
        println("Invalid package name: " + name + " (use lowercase letters, numbers, '.', '_' or '-')")
        ret false
    }
    ret true
}

fn init_project(name) {
    if (name == "") { name = "mon-paquet" }
    if (valid_name(name) == false) { ret 1 }
    if (gpm_read_file(MANIFEST) != "") {
        println("Manifest.toml already exists")
        ret 1
    }
    lt text = "# Goscript package manifest\n[metadata]\nname = \"" + name + "\"\nversion = \"0.1.0\"\nrelease = \"r0\"\narch = \"x86_64\"\ndescription = \"Goscript package\"\nauthor = \"\"\nlicense = \"MIT\"\nmain = \"main.gjs\"\nfiles = [\"__self__.gjs\", \"main.gjs\"]\n\n[dependencies]\n"
    if (gpm_write_file(MANIFEST, text) == 0) {
        println("Could not write Manifest.toml")
        ret 1
    }
    if (gpm_read_file("__self__.gjs") == "") {
        gpm_write_file("__self__.gjs", "golem " + name + "\npub fn package_name(): string {\n    ret \"" + name + "\"\n}\n")
    }
    if (gpm_read_file("main.gjs") == "") {
        gpm_write_file("main.gjs", "fn main() {\n    println(\"Welcome to " + name + "\")\n}\n")
    }
    ensure_dirs()
    println("Initialized project: " + name)
    ret 0
}

fn search(query) {
    if (query == "") { println("Usage: golem search <query>")
    ret 1 }
    lt data = gpm_http_get_response(REGISTRY + "/v5.2/package/search?q=" + gpm_url_encode(query), "")
    if (data == "") { println("Search failed (network or curl error)")
    ret 1 }
    if (gs_json_is(data) == 0) { println("Registry returned an invalid search response")
    ret 1 }
    lt error = gpm_json_get(data, "error")
    if (error != "") { println("Search failed: " + error)
    ret 1 }
    println(gpm_json_format(data))
    ret 0
}

fn info(name, version, scope) {
    if (name == "") { println("Usage: golem info <name> [version] [scope]")
    ret 1 }
    if (valid_name(name) == false) { ret 1 }
    lt url = REGISTRY + "/v5.2/package/" + name
    if (scope == "") { scope = "public" }
    url = url + "?scope=" + gpm_url_encode(scope)
    if (version != "") { url = url + "&version=" + gpm_url_encode(version) }
    lt data = gpm_http_get_response(url, "")
    if (data == "") { println("Could not reach the registry")
    ret 1 }
    if (gs_json_is(data) == 0) { println("Registry returned an invalid package response")
    ret 1 }
    lt error = gpm_json_get(data, "error")
    if (error != "") { println("Package lookup failed: " + error)
    ret 1 }
    println(gpm_json_format(data))
    ret 0
}

fn build() {
    lt name = gpm_manifest_get(MANIFEST, "name")
    lt version = gpm_manifest_get(MANIFEST, "version")
    lt release = gpm_manifest_get(MANIFEST, "release")
    lt arch = gpm_manifest_get(MANIFEST, "arch")
    if (name == "" || version == "") { println("Invalid Manifest.toml: metadata.name and metadata.version are required")
    ret 1 }
    if (release == "") { release = RELEASE }
    if (arch == "") { arch = ARCH }
    if (valid_name(name) == false) { ret 1 }
    ensure_dirs()
    lt archive = "build/" + name + "-" + version + "-" + release + "-" + arch + ".tar.bool"
    if (gpm_archive_build(".", archive) == 0) { println("Archive creation failed (tar is required)")
    ret 1 }
    println("Created archive: " + archive)
    ret 0
}

fn install_package(name, requested_version, depth) {
    if (depth > 12) { println("Maximum dependency depth reached")
    ret 1 }
    if (valid_name(name) == false) { ret 1 }
    ensure_dirs()
    lt marker = "modules/.golem-installing-" + name
    if (gpm_path_exists(marker) == 1) { ret 0 }
    lt url = REGISTRY + "/v5.2/package/" + name
    if (requested_version != "") { url = url + "?version=" + requested_version }
    lt detail = gpm_http_get_response(url, token())
    if (detail == "") { println("Could not retrieve package details for " + name)
    ret 1 }
    lt detail_error = gpm_json_get(detail, "error")
    if (detail_error != "") { println("Registry error: " + detail_error)
    ret 1 }
    lt version = gpm_json_get(detail, "version")
    lt release = gpm_json_get(detail, "release")
    lt arch = gpm_json_get(detail, "arch")
    lt scope = gpm_json_get(detail, "scope")
    lt expected = gpm_json_get(detail, "sha256")
    if (version == "" || scope == "") { println("Registry did not return metadata for " + name)
    ret 1 }
    if (release == "") { release = RELEASE }
    if (arch == "") { arch = ARCH }
    if (expected == "") { println("Missing SHA-256 checksum for " + name)
    ret 1 }
    lt archive = "build/.golem-download-" + name + ".tar.bool"
    lt download = REGISTRY + "/package/download/" + scope + "/" + name + "/" + version + "/" + release + "/" + arch
    if (gpm_http_download(download, archive, token()) == 0) { println("Download failed: " + name)
    ret 1 }
    lt actual = gpm_sha256_file(archive)
    if (actual == "" || actual != expected) {
        gpm_remove_tree(archive)
        println("SHA-256 mismatch for " + name + "; archive removed")
        ret 1
    }
    lt stage = "modules/.golem-stage-" + name
    gpm_remove_tree(stage)
    if (gpm_archive_extract(archive, stage) == 0) {
        gpm_remove_tree(archive)
        gpm_remove_tree(stage)
        println("Invalid archive or extraction failed: " + name)
        ret 1
    }
    gpm_remove_tree(archive)
    lt destination = "modules/" + name
    lt backup = "modules/.golem-backup-" + name
    gpm_remove_tree(backup)
    if (gpm_path_exists(destination) == 1 && gpm_move(destination, backup) == 0) {
        gpm_remove_tree(stage)
        println("Could not prepare replacement of " + name)
        ret 1
    }
    if (gpm_move(stage, destination) == 0) {
        if (gpm_path_exists(backup) == 1) { gpm_move(backup, destination) }
        gpm_remove_tree(stage)
        println("Could not install " + name)
        ret 1
    }
    gpm_remove_tree(backup)
    println("Installed: " + name + "@" + version)
    // Les dépendances sont résolues depuis le manifeste inclus dans l'archive.
    gpm_write_file(marker, "1")
    lt deps = gpm_manifest_dependencies(destination + "/Manifest.toml")
    lt lines = deps.split("\n")
    lt i = 0
    while (i < lines.len()) {
        lt row = lines[i]
        if (row != "") {
            lt pair = row.split_once("|")
            if (pair.len() == 2) {
                lt dep_name = pair[0].trim()
                lt dep_version = pair[1].trim()
                if (is_version_range(dep_version)) { dep_version = "" }
                if (dep_name != "" && install_package(dep_name, dep_version, depth + 1) != 0) {
                    gpm_remove_tree(marker)
                    println("Failed to install dependency " + dep_name + " required by " + name)
                    ret 1
                }
            }
        }
        i = i + 1
    }
    gpm_remove_tree(marker)
    ret 0
}

fn remove_package(name) {
    if (valid_name(name) == false) { ret 1 }
    if (gpm_path_exists("modules/" + name) == 0) { println("Package is not installed: " + name)
    ret 1 }
    if (gpm_remove_tree("modules/" + name) == 0) { println("Failed to remove package: " + name)
    ret 1 }
    println("Removed: " + name)
    ret 0
}

fn install_manifest_deps(update_all) {
    if (gpm_read_file(MANIFEST) == "") { println("Manifest.toml is missing; run golem init first")
    ret 1 }
    lt deps = gpm_manifest_dependencies(MANIFEST)
    lt lines = deps.split("\n")
    lt installed = 0
    lt i = 0
    while (i < lines.len()) {
        lt row = lines[i]
        if (row != "") {
            lt pair = row.split_once("|")
            if (pair.len() == 2) {
                lt dep_name = pair[0].trim()
                lt dep_version = pair[1].trim()
                if (update_all == true || is_version_range(dep_version)) { dep_version = "" }
                if (dep_name != "") {
                    if (install_package(dep_name, dep_version, 0) != 0) { ret 1 }
                    installed = installed + 1
                }
            }
        }
        i = i + 1
    }
    if (installed == 0) { println("No dependencies to install") }
    ret 0
}

fn login(username, password) {
    if (username == "") { println("Usage: golem login <username>")
    ret 1 }
    if (password == "") { password = gpm_prompt_secret("Password: ") }
    if (password == "") { println("Password input is unavailable in this terminal")
    ret 1 }
    ensure_dirs()
    lt body = "{\"username\":" + gpm_json_quote(username) + ",\"password\":" + gpm_json_quote(password) + "}"
    lt data = gpm_http_post_json(REGISTRY + "/v5.2/auth/login", body, "")
    lt auth_token = gpm_json_get(data, "token")
    lt authenticated_user = gpm_json_get(data, "username")
    if (auth_token == "" || authenticated_user == "") { println("Login failed: check your credentials and registry")
    ret 1 }
    if (gpm_write_secret(token_path(), auth_token + "\n") == 0) { println("Could not securely save the authentication token")
    ret 1 }
    if (gpm_write_secret(account_path(), authenticated_user + "\n") == 0) {
        gpm_remove_tree(token_path())
        println("Could not securely save the account name")
    ret 1 }
    println("Logged in as " + authenticated_user)
    ret 0
}

fn logout() {
    if (gpm_remove_tree(token_path()) == 0 || gpm_remove_tree(account_path()) == 0) {
        println("Could not remove saved credentials")
        ret 1
    }
    println("Logged out")
    ret 0
}

fn publish() {
    lt t = token()
    if (t == "") { println("Log in first with: golem login <username>")
    ret 1 }
    lt publisher = account()
    if (publisher == "") { println("Run golem login again to save your account for safe publishing")
    ret 1 }
    lt name = gpm_manifest_get(MANIFEST, "name")
    lt version = gpm_manifest_get(MANIFEST, "version")
    lt release = gpm_manifest_get(MANIFEST, "release")
    lt arch = gpm_manifest_get(MANIFEST, "arch")
    lt scope = gpm_manifest_get(MANIFEST, "scope")
    if (name == "" || version == "") { println("Manifest.toml must define metadata.name and metadata.version")
    ret 1 }
    if (valid_name(name) == false) { ret 1 }
    if (scope == "") { scope = "public" }
    if (valid_name(scope) == false) { println("Invalid publishing scope")
    ret 1 }
    if (release == "") { release = RELEASE }
    if (arch == "") { arch = ARCH }

    lt package_url = REGISTRY + "/v5.2/package/" + name + "?scope=" + gpm_url_encode(scope)
    lt existing = gpm_http_get_response(package_url, "")
    if (existing == "") { println("Cannot verify package ownership: registry is unreachable")
    ret 1 }
    lt lookup_error = gpm_json_get(existing, "error")
    if (lookup_error != "Package not found") {
        if (lookup_error != "") { println("Registry lookup failed: " + lookup_error)
        ret 1 }
        lt owner = gpm_json_get(existing, "author")
        if (owner == "") { println("Registry returned invalid package metadata; publish was stopped")
        ret 1 }
        if (owner != publisher) {
            println("Publish blocked: " + scope + "/" + name + " belongs to " + owner)
            println("Choose another package name or contact the owner.")
            ret 1
        }
    }

    if (build() != 0) { ret 1 }
    lt archive = "build/" + name + "-" + version + "-" + release + "-" + arch + ".tar.bool"
    lt filename = name + "-" + version + "-" + release + "-" + arch + ".tar.bool"

    if (lookup_error != "Package not found") {
        lt version_url = package_url + "&version=" + gpm_url_encode(version)
        lt version_info = gpm_http_get_response(version_url, "")
        if (version_info == "") { println("Cannot verify the version: registry is unreachable")
        ret 1 }
        lt version_error = gpm_json_get(version_info, "error")
        if (version_error == "") {
            lt remote_hash = gpm_json_get(version_info, "sha256")
            lt local_hash = gpm_sha256_file(archive)
            if (remote_hash != "" && remote_hash == local_hash) {
                println("Already published unchanged: " + scope + "/" + name + "@" + version)
                ret 0
            }
            println("Publish blocked: version " + version + " already exists with different contents")
            println("Bump metadata.version in Manifest.toml before publishing.")
            ret 1
        }
        if (version_error != "Package not found") { println("Version lookup failed: " + version_error)
        ret 1 }
    }

    lt endpoint = REGISTRY + "/v5.2/package/upload/" + scope + "/" + name
    if (gpm_http_upload(endpoint, archive, filename, t, version, release, arch) == 0) {
    ret 1 }
    println("Published: " + scope + "/" + name + "@" + version)
    ret 0
}

pub fn run(args) {
    lt argc = args.len()
    if (argc < 1) { help()
    ret 0 }
    lt command = args[0]
    if (command == "help" || command == "--help" || command == "-h") { help()
    ret 0 }
    if (command == "init") { lt name = ""
        if (argc > 1) { name = args[1] }
    ret init_project(name) }
    if (command == "search" || command == "s") { lt q = ""
        lt i = 1
        while (i < argc) {
            if (q != "") { q = q + " " }
            q = q + args[i]
            i = i + 1
        }
    ret search(q) }
    if (command == "info" || command == "show") { lt name = ""
        lt ver = ""
        lt package_scope = ""
        if (argc > 1) { name = args[1] }
        if (argc > 2) { ver = args[2] }
        if (argc > 3) { package_scope = args[3] }
    ret info(name, ver, package_scope) }
    if (command == "build") { ret build() }
    if (command == "install" || command == "i") { if (argc < 2) { ret install_manifest_deps(false) }
        lt ver = ""
        if (argc > 2) { ver = args[2] }
    ret install_package(args[1], ver, 0) }
    if (command == "remove" || command == "uninstall" || command == "rm") { if (argc < 2) { println("Usage: golem remove <package>")
        ret 1 }
    ret remove_package(args[1]) }
    if (command == "update" || command == "up") { if (argc < 2) { ret install_manifest_deps(true) }
    ret install_package(args[1], "", 0) }
    if (command == "list" || command == "ls") { println(gpm_list_packages("modules"))
    ret 0 }
    if (command == "login") { lt u = ""
        lt p = ""
        if (argc > 1) { u = args[1] }
        if (argc > 2) { p = args[2] }
    ret login(u, p) }
    if (command == "logout") { ret logout() }
    if (command == "publish") { ret publish() }
    if (command == "doctor") { doctor()
    ret 0 }
    println("Unknown command: " + command)
    help()
    ret 2
}

fn help() {
    println("Golem — Goscript package manager")
    println("Usage: golem <command> [arguments]")
    println("  init [name]                create Manifest.toml")
    println("  search <query>             search the registry (multiple words allowed)")
    println("  info <name> [version] [scope]  display package metadata")
    println("  install [name [version]]   install a package or dependencies")
    println("  remove <name>              remove a local package")
    println("  update [name]              update a package or dependencies")
    println("  list                       list installed packages")
    println("  login <username>           prompt for a password without echo")
    println("  logout                     remove saved credentials")
    println("  build                      create a .tar.bool archive")
    println("  publish                    publish to the configured registry")
    println("  doctor                     check required native tools")
    println("Examples:")
    println("  golem search http client")
    println("  golem info openv 0.1.1 public")
    println("  golem publish")
}

fn doctor() {
    println("Registry: " + REGISTRY)
    lt response = gpm_http_get_response(REGISTRY + "/status", "")
    if (response == "") { println("Registry connection: unavailable")
    } else { println("Registry connection: online") }
    if (token() == "") { println("Authentication: not logged in")
    } else if (account() == "") { println("Authentication: saved token; run golem login again")
    } else { println("Authentication: logged in as " + account()) }
    if (gpm_read_file(MANIFEST) == "") { println("Project manifest: not found")
    } else { println("Project manifest: " + MANIFEST) }
    println("Required tools: curl, tar, and sha256sum must be available on PATH.")
    println("Default package architecture: " + ARCH)
    println("Local installation directory: modules/")
}
