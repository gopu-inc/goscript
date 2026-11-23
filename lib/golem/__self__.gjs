golem golem

lt REGISTRY = "https://gsql-badge.onrender.com"
lt MANIFEST = "Manifest.toml"
lt RELEASE = "r0"
lt ARCH = "x86_64"

fn styled(text, red, green, blue) {
    ret text
}

fn accent(text) { ret styled(text, 86, 190, 245) }
fn muted(text) { ret styled(text, 135, 145, 158) }
fn positive(text) { ret styled(text, 101, 205, 150) }
fn negative(text) { ret styled(text, 245, 112, 112) }
fn number_text(value) { ret "" + value }

fn rule() {
    ret "------------------------------------------------"
}

fn headline(title) {
    println("")
    println(accent("golem") + " " + muted("package manager for Goscript"))
    println(muted(rule()))
    println(accent(title))
}

fn success(message) {
    println(positive("✓") + " " + message)
}

fn failure(message) {
    println(negative("✗") + " " + message)
}

fn detail(label, value) {
    if (value != "") {
        if (label == "") { println("    " + muted(value))
        } else { println("  " + muted(label) + "  " + value) }
    }
}

fn token_path() {
    ret gs_env_get("HOME") + "/.config/golem/token"
}

fn account_path() {
    ret gs_env_get("HOME") + "/.config/golem/account"
}

fn token() {
    ret gs_fs_read(token_path()).trim()
}

fn account() {
    ret gs_fs_read(account_path()).trim()
}

fn ensure_dirs() {
    gs_fs_mkdir("modules")
    gs_fs_mkdir("build")
    gs_fs_mkdir(gs_env_get("HOME") + "/.config/golem")
}

fn registry_get(url, auth_token) {
    if (auth_token == "") { ret gs_http_get(url) }
    ret gs_http_get_headers(url, "Authorization: Bearer " + auth_token)
}

fn manifest_value(path, key) {
    lt lines = gs_fs_read(path).split("\n")
    lt section = ""
    lt i = 0
    while (i < lines.len()) {
        lt line = lines[i].trim()
        if (line != "" && line[0] == "[") {
            section = line
        } else if (section == "[metadata]") {
            lt pair = line.split_once("=")
            if (pair.len() == 2 && pair[0].trim() == key) {
                lt value = pair[1].trim()
                if (value.len() >= 2 && value[0] == "\"" && value[value.len() - 1] == "\"") {
                    lt unquoted = ""
                    lt j = 1
                    while (j < value.len() - 1) {
                        unquoted = unquoted + value[j]
                        j = j + 1
                    }
                    ret unquoted
                }
                ret value
            }
        }
        i = i + 1
    }
    ret ""
}

fn is_version_range(value) {
    ret value.contains("^") || value.contains("~") || value.contains(">") || value == "*"
}

fn url_encode(value) {
    lt safe = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~"
    lt ascii = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
    lt hex = "0123456789ABCDEF"
    lt encoded = ""
    lt i = 0
    while (i < value.len()) {
        lt character = value[i]
        if (safe.contains(character)) {
            encoded = encoded + character
        } else {
            lt code = 0
            lt j = 0
            while (j < ascii.len()) {
                if (ascii[j] == character) {
                    code = j + 32
                    break
                }
                j = j + 1
            }
            if (code > 0) {
                encoded = encoded + "%" + hex[code / 16] + hex[code % 16]
            } else {
                encoded = encoded + character
            }
        }
        i = i + 1
    }
    ret encoded
}

fn valid_name(name) {
    if (gs_fs_valid_component(name) == 0 || name != name.lower() || name.contains("@")) {
        failure("Invalid package name: " + name + " (use lowercase letters, numbers, '.', '_' or '-')")
        ret false
    }
    ret true
}

fn init_project(name) {
    if (name == "") { name = "mon-paquet" }
    if (valid_name(name) == false) { ret 1 }
    if (gs_fs_read(MANIFEST) != "") {
        failure("Manifest.toml already exists")
        ret 1
    }
    lt text = "# Goscript package manifest\n[metadata]\nname = \"" + name + "\"\nversion = \"0.1.0\"\nrelease = \"r0\"\narch = \"x86_64\"\ndescription = \"Goscript package\"\nauthor = \"\"\nlicense = \"MIT\"\nmain = \"main.gjs\"\nfiles = [\"__self__.gjs\", \"main.gjs\"]\n\n[dependencies]\n"
    if (gs_fs_write(MANIFEST, text) == 0) {
        failure("Could not write Manifest.toml")
        ret 1
    }
    if (gs_fs_read("__self__.gjs") == "") {
        gs_fs_write("__self__.gjs", "golem " + name + "\npub fn package_name(): string {\n    ret \"" + name + "\"\n}\n")
    }
    if (gs_fs_read("main.gjs") == "") {
        gs_fs_write("main.gjs", "fn main() {\n    println(\"Welcome to " + name + "\")\n}\n")
    }
    ensure_dirs()
    success("Initialized " + name)
    println("  " + muted("Next") + "  golem install")
    ret 0
}

fn search(query) {
    if (query == "") { println("Usage: golem search <query>")
    ret 1 }
    lt data = registry_get(REGISTRY + "/v5.2/package/search?q=" + url_encode(query), "")
    if (data == "") { failure("Search failed (network or curl error)")
    ret 1 }
    lt error = gs_json_get(data, "error")
    if (error != "") { failure("Search failed: " + error)
    ret 1 }
    headline("Registry search")
    detail("Query", query)
    println(data)
    ret 0
}

fn info(name, version, scope) {
    if (name == "") { println("Usage: golem info <name> [version] [scope]")
    ret 1 }
    if (valid_name(name) == false) { ret 1 }
    lt url = REGISTRY + "/v5.2/package/" + name
    if (scope == "") { scope = "public" }
    url = url + "?scope=" + url_encode(scope)
    if (version != "") { url = url + "&version=" + url_encode(version) }
    lt data = registry_get(url, "")
    if (data == "") { failure("Could not reach the registry")
    ret 1 }
    lt error = gs_json_get(data, "error")
    if (error != "") { failure("Package lookup failed: " + error)
    ret 1 }
    lt package_name = gs_json_get(data, "name")
    lt package_version = gs_json_get(data, "version")
    lt package_scope = gs_json_get(data, "scope")
    lt author = gs_json_get(data, "author")
    lt release = gs_json_get(data, "release")
    lt arch = gs_json_get(data, "arch")
    lt downloads = gs_json_get(data, "downloads")
    lt size = gs_json_get(data, "size")
    lt created_at = gs_json_get(data, "created_at")
    lt checksum = gs_json_get(data, "sha256")
    if (package_name == "") { package_name = name }
    if (package_version == "") { package_version = version }
    headline("Package details")
    if (package_scope != "") { println("  " + accent(package_scope + "/" + package_name) + muted("@" + package_version))
    } else { println("  " + accent(package_name) + muted("@" + package_version)) }
    detail("Author", author)
    detail("Release", release)
    detail("Architecture", arch)
    detail("Downloads", downloads)
    detail("Archive size", size)
    detail("Published", created_at)
    detail("SHA-256", checksum)
    ret 0
}

fn build() {
    lt name = manifest_value(MANIFEST, "name")
    lt version = manifest_value(MANIFEST, "version")
    lt release = manifest_value(MANIFEST, "release")
    lt arch = manifest_value(MANIFEST, "arch")
    if (name == "" || version == "") { failure("Invalid Manifest.toml: metadata.name and metadata.version are required")
    ret 1 }
    if (release == "") { release = RELEASE }
    if (arch == "") { arch = ARCH }
    if (valid_name(name) == false) { ret 1 }
    ensure_dirs()
    lt archive = "build/" + name + "-" + version + "-" + release + "-" + arch + ".tar.bool"
    if (gs_which("tar") == "") { failure("Archive creation failed: tar is required")
    ret 1 }
    if (gs_archive_build(".", archive) == 0) { failure("Archive creation failed: every entry of 'files' in Manifest.toml must be an existing regular file (directories are not supported)")
    ret 1 }
    success("Built " + archive)
    detail("Size", number_text(gs_fs_size(archive)) + " bytes")
    ret 0
}

fn install_package(name, requested_version, depth) {
    if (depth > 12) { failure("Maximum dependency depth reached")
    ret 1 }
    if (valid_name(name) == false) { ret 1 }
    ensure_dirs()
    lt marker = "modules/.golem-installing-" + name
    if (gs_fs_exists(marker) == 1) { ret 0 }
    lt url = REGISTRY + "/v5.2/package/" + name
    if (requested_version != "") { url = url + "?version=" + requested_version }
    lt detail = registry_get(url, token())
    if (detail == "") { failure("Could not retrieve package details for " + name)
    ret 1 }
    lt detail_error = gs_json_get(detail, "error")
    if (detail_error != "") { failure("Registry error: " + detail_error)
    ret 1 }
    lt version = gs_json_get(detail, "version")
    lt release = gs_json_get(detail, "release")
    lt arch = gs_json_get(detail, "arch")
    lt scope = gs_json_get(detail, "scope")
    lt expected = gs_json_get(detail, "sha256")
    if (version == "" || scope == "") { failure("Registry did not return metadata for " + name)
    ret 1 }
    if (release == "") { release = RELEASE }
    if (arch == "") { arch = ARCH }
    if (expected == "") { failure("Missing SHA-256 checksum for " + name)
    ret 1 }
    lt archive = "build/.golem-download-" + name + ".tar.bool"
    lt download = REGISTRY + "/package/download/" + scope + "/" + name + "/" + version + "/" + release + "/" + arch
    if (gs_http_download(download, archive, token()) == 0) { failure("Download failed: " + name)
    ret 1 }
    lt actual = gs_hash_file(archive, "sha256")
    if (actual == "" || actual != expected) {
        gs_fs_remove(archive)
        failure("SHA-256 mismatch for " + name + "; archive removed")
        ret 1
    }
    lt stage = "modules/.golem-stage-" + name
    gs_fs_remove(stage)
    if (gs_tar_unpack(archive, stage) == 0) {
        gs_fs_remove(archive)
        gs_fs_remove(stage)
        failure("Invalid archive or extraction failed: " + name)
        ret 1
    }
    gs_fs_remove(archive)
    lt destination = "modules/" + name
    lt backup = "modules/.golem-backup-" + name
    gs_fs_remove(backup)
    if (gs_fs_exists(destination) == 1 && gs_fs_move(destination, backup) == 0) {
        gs_fs_remove(stage)
        failure("Could not prepare replacement of " + name)
        ret 1
    }
    if (gs_fs_move(stage, destination) == 0) {
        if (gs_fs_exists(backup) == 1) { gs_fs_move(backup, destination) }
        gs_fs_remove(stage)
        failure("Could not install " + name)
        ret 1
    }
    gs_fs_remove(backup)
    success("Installed " + name + "@" + version)
    // Les dépendances sont résolues depuis le manifeste inclus dans l'archive.
    gs_fs_write(marker, "1")
    lt deps = gs_manifest_dependencies(destination + "/Manifest.toml")
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
                    gs_fs_remove(marker)
                    failure("Failed to install dependency " + dep_name + " required by " + name)
                    ret 1
                }
            }
        }
        i = i + 1
    }
    gs_fs_remove(marker)
    ret 0
}

fn remove_package(name) {
    if (valid_name(name) == false) { ret 1 }
    if (gs_fs_exists("modules/" + name) == 0) { failure("Package is not installed: " + name)
    ret 1 }
    if (gs_fs_remove("modules/" + name) == 0) { failure("Failed to remove package: " + name)
    ret 1 }
    success("Removed " + name)
    ret 0
}

fn install_manifest_deps(update_all) {
    if (gs_fs_read(MANIFEST) == "") { failure("Manifest.toml is missing; run golem init first")
    ret 1 }
    lt deps = gs_manifest_dependencies(MANIFEST)
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
    if (installed == 0) { println(muted("No dependencies to install.")) }
    ret 0
}

fn login(username, password) {
    if (username == "") { println("Usage: golem login <username>")
    ret 1 }
    if (password == "") { password = gs_prompt_secret("Password: ") }
    if (password == "") { failure("Password input is unavailable in this terminal")
    ret 1 }
    ensure_dirs()
    lt body = "{\"username\":" + gs_json_quote(username) + ",\"password\":" + gs_json_quote(password) + "}"
    lt data = gs_http_post_json(REGISTRY + "/v5.2/auth/login", body, "")
    lt auth_token = gs_json_get(data, "token")
    lt authenticated_user = gs_json_get(data, "username")
    if (auth_token == "" || authenticated_user == "") { failure("Login failed: check your credentials and registry")
    ret 1 }
    if (gs_fs_write_private(token_path(), auth_token + "\n") == 0) { failure("Could not securely save the authentication token")
    ret 1 }
    if (gs_fs_write_private(account_path(), authenticated_user + "\n") == 0) {
        gs_fs_remove(token_path())
        failure("Could not securely save the account name")
    ret 1 }
    success("Logged in as " + authenticated_user)
    ret 0
}

fn logout() {
    if (gs_fs_remove(token_path()) == 0 || gs_fs_remove(account_path()) == 0) {
        failure("Could not remove saved credentials")
        ret 1
    }
    success("Logged out")
    ret 0
}

fn publish() {
    lt t = token()
    if (t == "") { failure("Log in first with: golem login <username>")
    ret 1 }
    lt publisher = account()
    if (publisher == "") { failure("Run golem login again to save your account for safe publishing")
    ret 1 }
    lt name = manifest_value(MANIFEST, "name")
    lt version = manifest_value(MANIFEST, "version")
    lt release = manifest_value(MANIFEST, "release")
    lt arch = manifest_value(MANIFEST, "arch")
    lt scope = manifest_value(MANIFEST, "scope")
    if (name == "" || version == "") { failure("Manifest.toml must define metadata.name and metadata.version")
    ret 1 }
    if (valid_name(name) == false) { ret 1 }
    if (scope == "") { scope = "public" }
    if (valid_name(scope) == false) { failure("Invalid publishing scope")
    ret 1 }
    if (release == "") { release = RELEASE }
    if (arch == "") { arch = ARCH }

    lt package_url = REGISTRY + "/v5.2/package/" + name + "?scope=" + url_encode(scope)
    lt existing = registry_get(package_url, "")
    if (existing == "") { failure("Cannot verify package ownership: registry is unreachable")
    ret 1 }
    lt lookup_error = gs_json_get(existing, "error")
    if (lookup_error != "Package not found") {
        if (lookup_error != "") { failure("Registry lookup failed: " + lookup_error)
        ret 1 }
        lt owner = gs_json_get(existing, "author")
        if (owner == "") { failure("Registry returned invalid package metadata; publish was stopped")
        ret 1 }
        if (owner != publisher) {
            failure("Publish blocked: " + scope + "/" + name + " belongs to " + owner)
            println("Choose another package name or contact the owner.")
            ret 1
        }
    }

    if (build() != 0) { ret 1 }
    lt archive = "build/" + name + "-" + version + "-" + release + "-" + arch + ".tar.bool"
    lt filename = name + "-" + version + "-" + release + "-" + arch + ".tar.bool"

    if (lookup_error != "Package not found") {
        lt version_url = package_url + "&version=" + url_encode(version)
        lt version_info = registry_get(version_url, "")
        if (version_info == "") { failure("Cannot verify the version: registry is unreachable")
        ret 1 }
        lt version_error = gs_json_get(version_info, "error")
        if (version_error == "") {
            lt remote_hash = gs_json_get(version_info, "sha256")
            lt local_hash = gs_hash_file(archive, "sha256")
            if (remote_hash != "" && remote_hash == local_hash) {
                success("Already published unchanged: " + scope + "/" + name + "@" + version)
                ret 0
            }
            failure("Publish blocked: version " + version + " already exists with different contents")
            println("Bump metadata.version in Manifest.toml before publishing.")
            ret 1
        }
        if (version_error != "Package not found") { failure("Version lookup failed: " + version_error)
        ret 1 }
    }

    lt endpoint = REGISTRY + "/v5.2/package/upload/" + scope + "/" + name
    if (gs_http_post_multipart_file(endpoint, archive, filename, t, version, release, arch) == 0) {
    ret 1 }
    success("Published " + scope + "/" + name + "@" + version)
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
    if (command == "list" || command == "ls") { list_packages()
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
    failure("Unknown command: " + command)
    help()
    ret 2
}

fn help() {
    headline("Goscript package manager")
    println("")
    println("Usage: golem <command> [arguments]")
    println("")
    println(accent("Packages"))
    println("  search <query>                 Search the registry")
    println("  info <name> [version] [scope]  Show package details")
    println("  install [name [version]]       Install a package, the runtime or dependencies")
    println("  remove <name>                  Remove an installed package")
    println("  update [name]                  Update a package or project dependencies")
    println("  list                           List installed packages")
    println("")
    println(accent("Project"))
    println("  init [name]                    Create a Goscript package")
    println("  build                          Build a .tar.bool archive")
    println("  publish                        Publish the current package")
    println("")
    println(accent("Account & diagnostics"))
    println("  login <username>               Sign in securely")
    println("  logout                         Remove saved credentials")
    println("  doctor                         Check registry and local tools")
    println("")
    println(muted("Examples"))
    println("  golem search http client")
    println("  golem info openv 0.1.1 public")
    println("  golem install")
    println("  golem publish")
}

fn list_packages() {
    lt raw = gs_fs_list_dir("modules")
    if (raw.trim() == "") {
        headline("Installed packages")
        println(muted("No packages installed."))
        ret
    }
    headline("Installed packages")
    lt names = raw.split(",")
    lt i = 0
    lt count = 0
    while (i < names.len()) {
        lt name = names[i].trim()
        if (name != "" && gs_fs_exists("modules/" + name + "/Manifest.toml") == 1) {
            lt version = manifest_value("modules/" + name + "/Manifest.toml", "version")
            if (version != "") {
                println("  " + accent(name) + muted("@" + version))
            } else {
                println("  " + accent(name))
            }
            count = count + 1
        }
        i = i + 1
    }
    println("")
    println(muted(number_text(count) + " packages installed."))
}

fn doctor() {
    headline("Environment check")
    detail("Registry", REGISTRY)
    lt response = registry_get(REGISTRY + "/status", "")
    if (response == "") { failure("Registry is unreachable")
    } else { success("Registry is online") }
    if (token() == "") { println(muted("Authentication: not logged in"))
    } else if (account() == "") { println(muted("Authentication: saved token; run golem login again"))
    } else { success("Logged in as " + account()) }
    if (gs_fs_read(MANIFEST) == "") { println(muted("No project manifest in this directory"))
    } else { success("Found " + MANIFEST) }
    if (gs_which("curl") == "") { failure("Required tool missing: curl")
    } else { success("curl is available") }
    if (gs_which("tar") == "") { failure("Required tool missing: tar")
    } else { success("tar is available") }
    if (gs_which("sha256sum") == "") { failure("Required tool missing: sha256sum")
    } else { success("sha256sum is available") }
    detail("Architecture", ARCH)
    detail("Install directory", "modules/")
}
