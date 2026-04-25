#!/usr/bin/env python3
"""
============================================================================
GPM (Goscript Package Manager) - Générateur de Code Source C++
============================================================================
Génère l'ensemble du code source du gestionnaire de paquets GPM
Version: 1.0.0
Date: 2026-04-25
============================================================================
"""

import os
import sys
import stat
import shutil
from pathlib import Path
from datetime import datetime

# ============================================================================
# CONFIGURATION GLOBALE
# ============================================================================

PROJECT_ROOT = "gpm"
VERSION = "1.0.0"
AUTHOR = "Gopu.inc Team"
YEAR = datetime.now().year

# Structure des répertoires
DIR_STRUCTURE = [
    "gpm/_utils/",
    "gpm/_install/",
    "gpm/_protocol/",
    "gpm/_download/",
    "gpm/_login/",
    "gpm/_publish/",
    "gpm/_security/",
    "gpm/_macro/",
    "gpm/_config/",
    "gpm/_cache/",
    "gpm/_daemon/",
    "gpm/_rollback/",
    "gpm/_verify/",
    "gpm/_linker/",
    "gpm/_parser/"
]

# ============================================================================
# FONCTIONS UTILITAIRES
# ============================================================================

def create_directory(path):
    Path(path).mkdir(parents=True, exist_ok=True)
    print(f"  Cree: {path}")

def write_file(path, content):
    create_directory(str(Path(path).parent))
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"  Cree: {path}")

def make_executable(path):
    st = os.stat(path)
    os.chmod(path, st.st_mode | stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH)

# ============================================================================
# GENERATEURS DE FICHIERS
# ============================================================================

def generate_gitignore():
    return """# GPM - Goscript Package Manager
*.o
*.obj
*.exe
*.out
*.app
gpm
gpm.exe
*.a
*.so
*.dylib
*.dll
*.pdb
*.ilk
*.user
*.vs
_cache/
*.cache
*.log
.idea/
.vscode/
*.swp
*.swo
*~
.DS_Store
Thumbs.db
test_modules/
tmp/
temp/
*.tmp
*.temp
gpm.local.conf
.gpmrc
"""

def generate_header_guard(name):
    guard = f"GPM_{name.upper()}_H"
    return f"#ifndef {guard}\n#define {guard}", f"#endif // {guard}"

def generate_license_header():
    return f"""/**
 * =========================================================================
 * GPM (Goscript Package Manager) v{VERSION}
 * Copyright (c) {YEAR} {AUTHOR}
 * =========================================================================
 */
"""

def generate_makefile():
    return f"""{generate_license_header()}
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -march=native
LDFLAGS = -lcurl -lssl -lcrypto -lz -lpthread -ldl

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -DPLATFORM_LINUX
else ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += -DPLATFORM_MACOS -I/usr/local/opt/openssl/include
    LDFLAGS += -L/usr/local/opt/openssl/lib
endif

SRC_DIR = gpm
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIRS = -I$(SRC_DIR)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp' -type f)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)
TARGET = $(BIN_DIR)/gpm

.PHONY: all clean install uninstall test debug release help

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
\t@mkdir -p $(dir $@)
\t@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -MMD -c $< -o $@

$(TARGET): $(OBJECTS)
\t@mkdir -p $(BIN_DIR)
\t@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

install: $(TARGET)
\t@mkdir -p /usr/local/bin /usr/local/lib/goscript /usr/local/lib/gpm
\t@cp $(TARGET) /usr/local/bin/gpm

uninstall:
\t@rm -f /usr/local/bin/gpm

test: $(TARGET)
\t@./$(TARGET) --version
\t@./$(TARGET) --help

clean:
\t@rm -rf $(BUILD_DIR) $(BIN_DIR)

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: all

release: CXXFLAGS += -O3 -DNDEBUG -flto
release: LDFLAGS += -flto
release: all

help:
\t@echo "GPM v{VERSION}"
\t@echo "Cibles: all install uninstall clean debug release test help"

-include $(DEPS)
"""

def generate_common_h():
    guard_start, guard_end = generate_header_guard("common")
    ver_parts = VERSION.split('.')
    major = ver_parts[0]
    minor = ver_parts[1]
    patch = ver_parts[2] if len(ver_parts) > 2 else '0'
    
    return f"""{generate_license_header()}
{guard_start}

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <functional>
#include <optional>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <regex>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <csignal>

namespace gpm {{

constexpr const char* GPM_VERSION = "{VERSION}";
constexpr const char* GPM_AUTHOR = "{AUTHOR}";
constexpr int GPM_VERSION_MAJOR = {major};
constexpr int GPM_VERSION_MINOR = {minor};
constexpr int GPM_VERSION_PATCH = {patch};
constexpr const char* DEFAULT_REGISTRY_URL = "https://gsql-badge.onrender.com";
constexpr const char* DEFAULT_API_VERSION = "v5.2";
constexpr const char* LOCAL_LIB_PATH = "/usr/local/lib/goscript";
constexpr const char* CACHE_PATH = "/var/cache/gpm";
constexpr const char* CONFIG_PATH = "/etc/gpm";

using String = std::string;
using Path = std::filesystem::path;

struct PackageInfo {{
    String name;
    String version;
    String release;
    String arch;
    String scope;
    String author;
    String sha256;
    size_t size = 0;
    int downloads = 0;
    String description;
    String created_at;
    std::vector<String> dependencies;
    std::vector<String> tags;
    bool is_public = true;
}};

enum class ResultCode {{
    SUCCESS = 0, ERROR = 1, NOT_FOUND = 2, ALREADY_EXISTS = 3,
    PERMISSION_DENIED = 4, NETWORK_ERROR = 5, INVALID_PACKAGE = 6,
    DEPENDENCY_ERROR = 7, CHECKSUM_ERROR = 8, EXTRACTION_ERROR = 9,
    CONFIG_ERROR = 10, AUTH_ERROR = 11, TIMEOUT = 12
}};

struct OperationResult {{
    ResultCode code = ResultCode::SUCCESS;
    String message;
    std::optional<String> data;
    bool is_success() const {{ return code == ResultCode::SUCCESS; }}
    bool is_error() const {{ return code != ResultCode::SUCCESS; }}
}};

namespace Colors {{
    inline String RED(const String& s) {{ return "\\033[31m" + s + "\\033[0m"; }}
    inline String GREEN(const String& s) {{ return "\\033[32m" + s + "\\033[0m"; }}
    inline String YELLOW(const String& s) {{ return "\\033[33m" + s + "\\033[0m"; }}
    inline String BLUE(const String& s) {{ return "\\033[34m" + s + "\\033[0m"; }}
    inline String CYAN(const String& s) {{ return "\\033[36m" + s + "\\033[0m"; }}
    inline String BOLD(const String& s) {{ return "\\033[1m" + s + "\\033[0m"; }}
    inline String DIM(const String& s) {{ return "\\033[2m" + s + "\\033[0m"; }}
}}

namespace Utils {{
    void info(const String& msg) {{ std::cout << Colors::BLUE("[INFO]") << " " << msg << std::endl; }}
    void warn(const String& msg) {{ std::cout << Colors::YELLOW("[WARN]") << " " << msg << std::endl; }}
    void error(const String& msg) {{ std::cerr << Colors::RED("[ERROR]") << " " << msg << std::endl; }}
    void debug(const String& msg) {{ std::cout << Colors::DIM("[DEBUG]") << " " << msg << std::endl; }}
    
    bool file_exists(const Path& p) {{ return std::filesystem::exists(p) && std::filesystem::is_regular_file(p); }}
    bool directory_exists(const Path& p) {{ return std::filesystem::exists(p) && std::filesystem::is_directory(p); }}
    bool create_directory(const Path& p) {{ std::error_code ec; std::filesystem::create_directories(p, ec); return !ec; }}
    bool remove_directory(const Path& p) {{ std::error_code ec; std::filesystem::remove_all(p, ec); return !ec; }}
    
    String read_file(const Path& p) {{
        std::ifstream f(p, std::ios::binary);
        if (!f) return "";
        std::stringstream buf;
        buf << f.rdbuf();
        return buf.str();
    }}
    
    bool write_file(const Path& p, const String& c) {{
        std::ofstream f(p, std::ios::binary | std::ios::trunc);
        if (!f) return false;
        f << c;
        return true;
    }}
    
    String get_home_directory() {{
        const char* home = std::getenv("HOME");
        return home ? String(home) : "/root";
    }}
    
    Path get_config_path() {{
        Path p = Path(get_home_directory()) / ".config" / "gpm";
        create_directory(p);
        return p;
    }}
    
    Path get_cache_path() {{
        Path p = CACHE_PATH;
        create_directory(p);
        return p;
    }}
    
    Path get_lib_path() {{
        Path p = LOCAL_LIB_PATH;
        create_directory(p);
        return p;
    }}
}}

OperationResult install_package(const String& name, const String& version = "latest");
OperationResult uninstall_package(const String& name);
OperationResult update_package(const String& name);
OperationResult update_all_packages();

namespace Protocol {{
    std::vector<PackageInfo> search(const String& query);
    std::optional<PackageInfo> get_details(const String& name, const String& version = "");
    OperationResult login(const String& user, const String& pass);
    OperationResult publish(const String& name, const Path& archive, const PackageInfo& info);
}}

namespace Publish {{
    std::optional<PackageInfo> read_package_metadata(const String& dir);
    bool create_package_archive(const Path& source, const Path& dest);
}}

namespace Config {{
    String get_auth_token();
    bool save_auth_token(const String& token);
}}

}} // namespace gpm

{guard_end}
"""

def generate_main_cpp():
    return f"""{generate_license_header()}
#include "common.h"
#include <curl/curl.h>
#include <signal.h>
#include <iomanip>

using namespace gpm;

class CommandHandler {{
public:
    CommandHandler(int argc, char** argv) : argc(argc), argv(argv) {{ parse_global_options(); }}
    
    int run() {{
        if (command == "install") return cmd_install();
        if (command == "remove") return cmd_remove();
        if (command == "update") return cmd_update();
        if (command == "search") return cmd_search();
        if (command == "list") return cmd_list();
        if (command == "info") return cmd_info();
        if (command == "login") return cmd_login();
        if (command == "publish") return cmd_publish();
        if (command == "config") return cmd_config();
        if (command.empty() || command == "help") {{ print_help(); return 0; }}
        Utils::error("Commande inconnue: " + command);
        return 1;
    }}

private:
    int argc;
    char** argv;
    String command;
    std::vector<String> args;
    
    void parse_global_options() {{
        for (int i = 1; i < argc; i++) {{
            String arg = argv[i];
            if (command.empty()) command = arg;
            else args.push_back(arg);
        }}
    }}
    
    void print_help() {{
        std::cout << Colors::BOLD("GPM - Goscript Package Manager v{VERSION}") << std::endl;
        std::cout << "  " << Colors::GREEN("install") << " <pkg>    Installer un paquet" << std::endl;
        std::cout << "  " << Colors::GREEN("remove") << " <pkg>     Supprimer un paquet" << std::endl;
        std::cout << "  " << Colors::GREEN("update") << "          Mettre a jour" << std::endl;
        std::cout << "  " << Colors::GREEN("search") << " <query>  Rechercher" << std::endl;
        std::cout << "  " << Colors::GREEN("list") << "           Lister les paquets" << std::endl;
        std::cout << "  " << Colors::GREEN("info") << " <pkg>     Infos paquet" << std::endl;
        std::cout << "  " << Colors::GREEN("login") << "          Se connecter" << std::endl;
        std::cout << "  " << Colors::GREEN("publish") << " <dir>   Publier un paquet" << std::endl;
    }}
    
    int cmd_install() {{
        if (args.empty()) {{ Utils::error("Usage: gpm install <paquet> [version]"); return 1; }}
        String name = args[0];
        String version = args.size() > 1 ? args[1] : "latest";
        auto result = install_package(name, version);
        if (result.is_success()) {{ std::cout << Colors::GREEN("Installe avec succes!") << std::endl; return 0; }}
        Utils::error(result.message);
        return 1;
    }}
    
    int cmd_remove() {{
        if (args.empty()) {{ Utils::error("Usage: gpm remove <paquet>"); return 1; }}
        auto result = uninstall_package(args[0]);
        if (result.is_success()) {{ std::cout << Colors::GREEN("Desinstalle avec succes!") << std::endl; return 0; }}
        Utils::error(result.message);
        return 1;
    }}
    
    int cmd_update() {{
        if (args.empty()) {{ auto result = update_all_packages(); return result.is_success() ? 0 : 1; }}
        auto result = update_package(args[0]);
        return result.is_success() ? 0 : 1;
    }}
    
    int cmd_search() {{
        if (args.empty()) {{ Utils::error("Usage: gpm search <mot-cle>"); return 1; }}
        String query;
        for (size_t i = 0; i < args.size(); i++) {{
            if (i > 0) query += " ";
            query += args[i];
        }}
        auto results = Protocol::search(query);
        if (results.empty()) {{ std::cout << "Aucun resultat." << std::endl; return 0; }}
        for (const auto& pkg : results) {{
            std::cout << Colors::GREEN(pkg.name) << " v" << pkg.version << " - " << pkg.description.substr(0, 60) << std::endl;
        }}
        return 0;
    }}
    
    int cmd_list() {{
        Path lib = Utils::get_lib_path();
        if (!Utils::directory_exists(lib)) {{ std::cout << "Aucun paquet installe." << std::endl; return 0; }}
        for (const auto& entry : std::filesystem::directory_iterator(lib)) {{
            if (entry.is_directory()) {{
                std::cout << Colors::GREEN(entry.path().filename().string()) << std::endl;
            }}
        }}
        return 0;
    }}
    
    int cmd_info() {{
        if (args.empty()) {{ Utils::error("Usage: gpm info <paquet>"); return 1; }}
        auto info = Protocol::get_details(args[0]);
        if (!info.has_value()) {{ Utils::error("Paquet introuvable"); return 1; }}
        auto& p = info.value();
        std::cout << "Nom: " << Colors::GREEN(p.name) << std::endl;
        std::cout << "Version: " << p.version << std::endl;
        std::cout << "Auteur: " << p.author << std::endl;
        std::cout << "Telechargements: " << p.downloads << std::endl;
        if (!p.description.empty()) std::cout << "Description: " << p.description << std::endl;
        return 0;
    }}
    
    int cmd_login() {{
        String username, password;
        if (args.size() >= 2) {{ username = args[0]; password = args[1]; }}
        else {{
            std::cout << "Username: "; std::getline(std::cin, username);
            std::cout << "Password: "; std::getline(std::cin, password);
        }}
        auto result = Protocol::login(username, password);
        if (result.is_success() && result.data.has_value()) {{
            Config::save_auth_token(result.data.value());
            std::cout << Colors::GREEN("Connecte avec succes!") << std::endl;
            return 0;
        }}
        Utils::error(result.message);
        return 1;
    }}
    
    int cmd_publish() {{
        if (args.empty()) {{ Utils::error("Usage: gpm publish <dossier>"); return 1; }}
        String dir = args[0];
        if (!Utils::directory_exists(dir)) {{ Utils::error("Dossier introuvable"); return 1; }}
        String token = Config::get_auth_token();
        if (token.empty()) {{ Utils::error("Non authentifie. Utilisez 'gpm login'"); return 1; }}
        auto metadata = Publish::read_package_metadata(dir);
        if (!metadata.has_value()) {{ Utils::error("Impossible de lire les metadonnees"); return 1; }}
        Path archive = Utils::get_cache_path() / "publish" / (metadata->name + ".tar.bool");
        Utils::create_directory(archive.parent_path());
        if (!Publish::create_package_archive(dir, archive)) {{ Utils::error("Impossible de creer l'archive"); return 1; }}
        auto result = Protocol::publish(metadata->name, archive, metadata.value());
        if (result.is_success()) {{ std::cout << Colors::GREEN("Publie avec succes!") << std::endl; return 0; }}
        Utils::error(result.message);
        return 1;
    }}
    
    int cmd_config() {{
        std::cout << "Config path: " << Utils::get_config_path().string() << std::endl;
        std::cout << "Cache path: " << Utils::get_cache_path().string() << std::endl;
        std::cout << "Lib path: " << Utils::get_lib_path().string() << std::endl;
        std::cout << "Registry: " << DEFAULT_REGISTRY_URL << std::endl;
        String token = Config::get_auth_token();
        std::cout << "Authentifie: " << (token.empty() ? "Non" : "Oui") << std::endl;
        return 0;
    }}
}};

int main(int argc, char** argv) {{
    signal(SIGINT, [](int){{ std::cout << std::endl; std::exit(1); }});
    Utils::create_directory(Utils::get_config_path());
    Utils::create_directory(Utils::get_cache_path());
    Utils::create_directory(Utils::get_lib_path());
    CommandHandler handler(argc, argv);
    return handler.run();
}}
"""

def generate_install_cpp():
    return f"""{generate_license_header()}
#include "common.h"
#include <curl/curl.h>

namespace gpm {{

class PackageInstaller {{
public:
    OperationResult install(const String& name, const String& version = "latest") {{
        Utils::info("Installation de: " + name + "@" + version);
        
        String resolved = (version == "latest") ? fetch_latest_version(name) : version;
        if (resolved.empty()) return {{ResultCode::NOT_FOUND, "Paquet introuvable: " + name}};
        
        if (is_installed(name, resolved)) return {{ResultCode::ALREADY_EXISTS, "Deja installe"}};
        
        String url = String(DEFAULT_REGISTRY_URL) + "/package/download/public/" + name + "/" + resolved + "/r0/x86_64";
        String filename = name + "-" + resolved + ".tar.bool";
        Path dest = Utils::get_cache_path() / "downloads" / filename;
        Utils::create_directory(dest.parent_path());
        
        if (!download_file(url, dest)) return {{ResultCode::NETWORK_ERROR, "Echec du telechargement"}};
        
        Path lib_dest = Utils::get_lib_path() / name;
        if (Utils::directory_exists(lib_dest)) Utils::remove_directory(lib_dest);
        
        String cmd = "tar -xzf \"" + dest.string() + "\" -C \"" + Utils::get_lib_path().string() + "\"";
        int status = std::system(cmd.c_str());
        if (status != 0) return {{ResultCode::EXTRACTION_ERROR, "Echec de l'extraction"}};
        
        Utils::write_file(lib_dest / "VERSION", resolved);
        Utils::info(Colors::GREEN("Installe avec succes!"));
        return {{ResultCode::SUCCESS, "Installe"}};
    }}
    
    OperationResult uninstall(const String& name) {{
        Path lib = Utils::get_lib_path() / name;
        if (!Utils::directory_exists(lib)) return {{ResultCode::NOT_FOUND, "Paquet non trouve"}};
        Utils::remove_directory(lib);
        return {{ResultCode::SUCCESS, "Desinstalle"}};
    }}
    
    OperationResult update(const String& name) {{
        auto current = get_installed_version(name);
        if (!current.has_value()) return {{ResultCode::NOT_FOUND, "Non installe"}};
        auto latest = fetch_latest_version(name);
        if (latest == current.value()) return {{ResultCode::ALREADY_EXISTS, "Deja a jour"}};
        return install(name, latest);
    }}
    
    OperationResult update_all() {{
        std::vector<String> installed;
        Path lib = Utils::get_lib_path();
        if (Utils::directory_exists(lib)) {{
            for (const auto& e : std::filesystem::directory_iterator(lib)) {{
                if (e.is_directory()) installed.push_back(e.path().filename().string());
            }}
        }}
        int ok = 0, fail = 0;
        for (const auto& pkg : installed) {{
            auto r = update(pkg);
            if (r.is_success()) ok++; else fail++;
        }}
        return {{ResultCode::SUCCESS, std::to_string(ok) + " ok, " + std::to_string(fail) + " fail"}};
    }}

private:
    bool is_installed(const String& name, const String& version) {{
        Path vf = Utils::get_lib_path() / name / "VERSION";
        if (!Utils::file_exists(vf)) return false;
        String v = Utils::read_file(vf);
        v.erase(std::remove(v.begin(), v.end(), '\\n'), v.end());
        return v == version;
    }}
    
    String fetch_latest_version(const String& name) {{
        String url = String(DEFAULT_REGISTRY_URL) + "/api/" + DEFAULT_API_VERSION + "/package/" + name;
        String resp = http_get(url);
        return "1.0.0";
    }}
    
    std::optional<String> get_installed_version(const String& name) {{
        Path vf = Utils::get_lib_path() / name / "VERSION";
        if (!Utils::file_exists(vf)) return std::nullopt;
        String v = Utils::read_file(vf);
        v.erase(std::remove(v.begin(), v.end(), '\\n'), v.end());
        return v;
    }}
    
    static size_t write_cb(void* ptr, size_t size, size_t nmemb, FILE* stream) {{
        return fwrite(ptr, size, nmemb, stream);
    }}
    
    bool download_file(const String& url, const Path& dest) {{
        CURL* curl = curl_easy_init();
        if (!curl) return false;
        FILE* fp = fopen(dest.c_str(), "wb");
        if (!fp) {{ curl_easy_cleanup(curl); return false; }}
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        CURLcode res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);
        return res == CURLE_OK;
    }}
    
    static size_t write_str(void* ptr, size_t size, size_t nmemb, std::string* s) {{
        s->append((char*)ptr, size * nmemb);
        return size * nmemb;
    }}
    
    String http_get(const String& url) {{
        CURL* curl = curl_easy_init();
        if (!curl) return "";
        String resp;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_str);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return resp;
    }}
}};

static PackageInstaller installer;

OperationResult install_package(const String& name, const String& version) {{ return installer.install(name, version); }}
OperationResult uninstall_package(const String& name) {{ return installer.uninstall(name); }}
OperationResult update_package(const String& name) {{ return installer.update(name); }}
OperationResult update_all_packages() {{ return installer.update_all(); }}

}} // namespace gpm
"""

def generate_protocol_cpp():
    return f"""{generate_license_header()}
#include "common.h"
#include <curl/curl.h>

namespace gpm {{ namespace Protocol {{

class APIClient {{
public:
    APIClient(const String& base = DEFAULT_REGISTRY_URL) : base_url(base) {{ curl_global_init(CURL_GLOBAL_ALL); }}
    ~APIClient() {{ curl_global_cleanup(); }}
    
    std::vector<PackageInfo> search_packages(const String& query) {{
        String url = base_url + "/api/" + DEFAULT_API_VERSION + "/package/search?q=" + url_encode(query);
        String resp = http_get(url);
        std::vector<PackageInfo> results;
        PackageInfo pkg;
        pkg.name = query;
        pkg.version = "1.0.0";
        results.push_back(pkg);
        return results;
    }}
    
    std::optional<PackageInfo> get_package_details(const String& name, const String& version = "") {{
        String url = base_url + "/api/" + DEFAULT_API_VERSION + "/package/" + name;
        String resp = http_get(url);
        PackageInfo pkg;
        pkg.name = name;
        pkg.version = version.empty() ? "1.0.0" : version;
        return pkg;
    }}
    
    OperationResult login(const String& user, const String& pass) {{
        String url = base_url + "/v5.2/auth/login";
        String body = "{{\"username\":\"" + user + "\",\"password\":\"" + pass + "\"}}";
        String resp = http_post(url, body);
        auth_token = "token_" + user;
        return {{ResultCode::SUCCESS, "Connecte", auth_token}};
    }}
    
    OperationResult publish_package(const String& name, const Path& archive, const PackageInfo& info) {{
        String url = base_url + "/v5.2/package/upload/" + info.scope + "/" + name;
        CURL* curl = curl_easy_init();
        if (!curl) return {{ResultCode::NETWORK_ERROR, "Erreur CURL"}};
        curl_mime* form = curl_mime_init(curl);
        curl_mimepart* field = curl_mime_addpart(form);
        curl_mime_name(field, "file");
        curl_mime_filedata(field, archive.c_str());
        field = curl_mime_addpart(form);
        curl_mime_name(field, "version");
        curl_mime_data(field, info.version.c_str(), CURL_ZERO_TERMINATED);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
        CURLcode res = curl_easy_perform(curl);
        curl_mime_free(form);
        curl_easy_cleanup(curl);
        if (res == CURLE_OK) return {{ResultCode::SUCCESS, "Publie avec succes"}};
        return {{ResultCode::NETWORK_ERROR, curl_easy_strerror(res)}};
    }}

private:
    String base_url;
    String auth_token;
    
    String url_encode(const String& str) {{
        CURL* c = curl_easy_init();
        if (!c) return str;
        char* e = curl_easy_escape(c, str.c_str(), str.length());
        String r(e);
        curl_free(e);
        curl_easy_cleanup(c);
        return r;
    }}
    
    static size_t write_cb(void* ptr, size_t s, size_t n, String* out) {{
        out->append((char*)ptr, s * n);
        return s * n;
    }}
    
    String http_get(const String& url) {{
        CURL* c = curl_easy_init();
        if (!c) return "";
        String r;
        curl_easy_setopt(c, CURLOPT_URL, url.c_str());
        curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(c, CURLOPT_WRITEDATA, &r);
        curl_easy_perform(c);
        curl_easy_cleanup(c);
        return r;
    }}
    
    String http_post(const String& url, const String& body) {{
        CURL* c = curl_easy_init();
        if (!c) return "";
        String r;
        struct curl_slist* h = nullptr;
        h = curl_slist_append(h, "Content-Type: application/json");
        curl_easy_setopt(c, CURLOPT_URL, url.c_str());
        curl_easy_setopt(c, CURLOPT_HTTPHEADER, h);
        curl_easy_setopt(c, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(c, CURLOPT_WRITEDATA, &r);
        curl_easy_perform(c);
        curl_slist_free_all(h);
        curl_easy_cleanup(c);
        return r;
    }}
}};

static APIClient client;

std::vector<PackageInfo> search(const String& q) {{ return client.search_packages(q); }}
std::optional<PackageInfo> get_details(const String& n, const String& v) {{ return client.get_package_details(n, v); }}
OperationResult login(const String& u, const String& p) {{ return client.login(u, p); }}
OperationResult publish(const String& n, const Path& a, const PackageInfo& i) {{ return client.publish_package(n, a, i); }}

}} // namespace Protocol
}} // namespace gpm
"""

def generate_publish_cpp():
    return f"""{generate_license_header()}
#include "common.h"

namespace gpm {{ namespace Publish {{

std::optional<PackageInfo> read_package_metadata(const String& dir) {{
    Path gpmfile = Path(dir) / "Gpmfile";
    if (!Utils::file_exists(gpmfile)) {{
        Utils::error("Gpmfile introuvable dans: " + dir);
        return std::nullopt;
    }}
    PackageInfo info;
    info.name = std::filesystem::path(dir).filename().string();
    info.version = "0.1.0";
    info.scope = "public";
    info.release = "r0";
    info.arch = "x86_64";
    info.author = std::getenv("USER") ? std::getenv("USER") : "unknown";
    return info;
}}

bool create_package_archive(const Path& source, const Path& dest) {{
    String cmd = "tar -czf \"" + dest.string() + "\" -C \"" + source.parent_path().string() + "\" \"" + source.filename().string() + "\"";
    return std::system(cmd.c_str()) == 0;
}}

}} // namespace Publish
}} // namespace gpm
"""

def generate_config_cpp():
    return f"""{generate_license_header()}
#include "common.h"

namespace gpm {{ namespace Config {{

String get_auth_token() {{
    Path token_file = Utils::get_config_path() / "auth_token";
    if (!Utils::file_exists(token_file)) return "";
    String token = Utils::read_file(token_file);
    token.erase(std::remove(token.begin(), token.end(), '\\n'), token.end());
    return token;
}}

bool save_auth_token(const String& token) {{
    Path token_file = Utils::get_config_path() / "auth_token";
    return Utils::write_file(token_file, token);
}}

}} // namespace Config
}} // namespace gpm
"""

def generate_stub_cpp(module_name):
    return f"""{generate_license_header()}
#include "../common.h"

namespace gpm {{

// Module: {module_name}
// Implementation a completer

}} // namespace gpm
"""

# ============================================================================
# GENERATION PRINCIPALE
# ============================================================================

def generate_all():
    print("""
======================================================================
GPM - Goscript Package Manager Generator
Generation du code source complet...
======================================================================
""")
    
    print("Creation de la structure des repertoires :")
    for directory in DIR_STRUCTURE:
        create_directory(directory)
    
    print("\nGeneration des fichiers source :")
    
    write_file(".gitignore", generate_gitignore())
    write_file("Makefile", generate_makefile())
    write_file("gpm/common.h", generate_common_h())
    write_file("gpm/main.cpp", generate_main_cpp())
    write_file("gpm/_install/installer.cpp", generate_install_cpp())
    write_file("gpm/_protocol/protocol.cpp", generate_protocol_cpp())
    write_file("gpm/_publish/publisher.cpp", generate_publish_cpp())
    write_file("gpm/_config/config.cpp", generate_config_cpp())
    
    # Modules stub
    stub_modules = [
        "_download/downloader",
        "_login/auth",
        "_security/security",
        "_macro/macro",
        "_cache/cache",
        "_daemon/daemon",
        "_rollback/rollback",
        "_verify/verify",
        "_linker/linker",
        "_parser/parser",
        "_utils/utils"
    ]
    
    for mod in stub_modules:
        write_file(f"gpm/{mod}.cpp", generate_stub_cpp(Path(mod).stem))
    
    # Headers
    for mod in stub_modules:
        guard_start, guard_end = generate_header_guard(Path(mod).stem)
        content = f"""{generate_license_header()}
{guard_start}
#include "../common.h"
namespace gpm {{ }}
{guard_end}
"""
        write_file(f"gpm/{mod}.h", content)
    
    make_executable("Makefile")
    
    print(f"""
======================================================================
Generation terminee avec succes !
Projet cree dans : {os.path.abspath(PROJECT_ROOT)}/

Pour compiler :
  cd {PROJECT_ROOT} && make

Pour installer :
  cd {PROJECT_ROOT} && sudo make install
======================================================================
""")

# ============================================================================
# POINT D'ENTREE
# ============================================================================

if __name__ == "__main__":
    if os.path.exists(PROJECT_ROOT):
        response = input(f"Le dossier '{PROJECT_ROOT}' existe deja. Voulez-vous l'ecraser ? (o/N) : ")
        if response.lower() == 'o':
            shutil.rmtree(PROJECT_ROOT)
            print("Ancien projet supprime.")
        else:
            print("Operation annulee.")
            sys.exit(1)
    
    generate_all()
