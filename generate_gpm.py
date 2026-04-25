Je vais créer un générateur Python complet qui va produire tout le code C++ pour le GPM (Goscript Package Manager). Ce sera un système modulaire et robuste.

```python
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

def create_directory(path: str) -> None:
    """Crée un répertoire avec tous les parents nécessaires."""
    Path(path).mkdir(parents=True, exist_ok=True)
    print(f"  📁 Créé: {path}")

def write_file(path: str, content: str) -> None:
    """Écrit un fichier avec son contenu."""
    create_directory(str(Path(path).parent))
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"  📄 Créé: {path}")

def make_executable(path: str) -> None:
    """Rend un fichier exécutable."""
    st = os.stat(path)
    os.chmod(path, st.st_mode | stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH)

# ============================================================================
# GÉNÉRATEURS DE FICHIERS
# ============================================================================

def generate_gitignore() -> str:
    """Génère le .gitignore."""
    return """# GPM - Goscript Package Manager
# Fichiers ignorés par Git

# Compilés
*.o
*.obj
*.exe
*.out
*.app
gpm
gpm.exe

# Bibliothèques
*.a
*.so
*.dylib
*.dll

# Débogage
*.pdb
*.ilk
*.user
*.vs

# Cache
_cache/
*.cache
*.log

# IDE
.idea/
.vscode/
*.swp
*.swo
*~
.DS_Store
Thumbs.db

# Paquets installés localement (pour les tests)
test_modules/

# Fichiers temporaires
tmp/
temp/
*.tmp
*.temp

# Configuration locale
gpm.local.conf
.gpmrc
"""

def generate_header_guard(name: str) -> tuple:
    """Génère les gardes d'en-tête C++."""
    guard = f"GPM_{name.upper()}_H"
    return f"#ifndef {guard}\n#define {guard}", f"#endif // {guard}"

def generate_license_header() -> str:
    """Génère l'en-tête de licence."""
    return f"""/**
 * =========================================================================
 * GPM (Goscript Package Manager) v{VERSION}
 * Copyright (c) {YEAR} {AUTHOR}
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * =========================================================================
 */
"""

def generate_makefile() -> str:
    """Génère le Makefile principal."""
    return f"""{generate_license_header()}

# ============================================================================
# GPM - Makefile
# ============================================================================

# Compilateur et flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -march=native
LDFLAGS = -lcurl -lssl -lcrypto -lz -lpthread -ldl

# Architecture
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -DPLATFORM_LINUX
else ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += -DPLATFORM_MACOS
    CXXFLAGS += -I/usr/local/opt/openssl/include
    LDFLAGS += -L/usr/local/opt/openssl/lib
else
    $(error Unsupported platform: $(UNAME_S))
endif

# Répertoires
SRC_DIR = gpm
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIRS = -I$(SRC_DIR)

# Sources (tous les .cpp dans gpm/ et ses sous-répertoires)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp' -type f)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

# Cible principale
TARGET = $(BIN_DIR)/gpm

# Couleurs
GREEN = \\033[0;32m
YELLOW = \\033[1;33m
RED = \\033[0;31m
NC = \\033[0m

.PHONY: all clean install uninstall test debug release help

all: $(TARGET)

# Règle de compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
\t@mkdir -p $(dir $@)
\t@echo "$(YELLOW)[CXX]$(NC) $<"
\t@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -MMD -c $< -o $@

# Édition de liens
$(TARGET): $(OBJECTS)
\t@mkdir -p $(BIN_DIR)
\t@echo "$(GREEN)[LD]$(NC) $@"
\t@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
\t@echo ""
\t@echo "$(GREEN)╔════════════════════════════════════════════════════════╗$(NC)"
\t@echo "$(GREEN)║        GPM v{VERSION} compilé avec succès !        ║$(NC)"
\t@echo "$(GREEN)╚════════════════════════════════════════════════════════╝$(NC)"
\t@echo ""

# Installation
install: $(TARGET)
\t@echo "$(YELLOW)Installation de GPM...$(NC)"
\t@mkdir -p /usr/local/bin
\t@mkdir -p /usr/local/lib/goscript
\t@mkdir -p /usr/local/lib/gpm
\t@cp $(TARGET) /usr/local/bin/gpm
\t@echo "$(GREEN)✅ GPM installé avec succès !$(NC)"

# Désinstallation
uninstall:
\t@echo "$(RED)Désinstallation de GPM...$(NC)"
\t@rm -f /usr/local/bin/gpm
\t@echo "$(GREEN)✅ GPM désinstallé.$(NC)"

# Tests
test: $(TARGET)
\t@echo "$(YELLOW)Exécution des tests...$(NC)"
\t@./$(TARGET) --version
\t@./$(TARGET) --help

# Nettoyage
clean:
\t@echo "$(RED)Nettoyage...$(NC)"
\t@rm -rf $(BUILD_DIR)
\t@rm -rf $(BIN_DIR)
\t@echo "$(GREEN)✅ Nettoyé.$(NC)"

# Debug
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: all

# Release optimisé
release: CXXFLAGS += -O3 -DNDEBUG -flto
release: LDFLAGS += -flto
release: all

# Aide
help:
\t@echo "GPM (Goscript Package Manager) v{VERSION}"
\t@echo ""
\t@echo "Cibles disponibles:"
\t@echo "  all        - Compile GPM"
\t@echo "  install    - Installe GPM dans /usr/local/bin"
\t@echo "  uninstall  - Désinstalle GPM"
\t@echo "  clean      - Nettoie les fichiers de compilation"
\t@echo "  debug      - Compile en mode debug"
\t@echo "  release    - Compile avec optimisations maximales"
\t@echo "  test       - Exécute les tests de base"
\t@echo "  help       - Affiche cette aide"

# Inclure les fichiers de dépendances
-include $(DEPS)
"""

def generate_common_h() -> str:
    """Génère gpm/common.h - Définitions communes."""
    guard_start, guard_end = generate_header_guard("common")
    
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

// ============================================================================
// CONFIGURATION GLOBALE
// ============================================================================

namespace gpm {{

// Version
constexpr const char* GPM_VERSION = "{VERSION}";
constexpr const char* GPM_AUTHOR = "{AUTHOR}";
constexpr int GPM_VERSION_MAJOR = {VERSION.split('.')[0]};
constexpr int GPM_VERSION_MINOR = {VERSION.split('.')[1]};
constexpr int GPM_VERSION_PATCH = {VERSION.split('.')[2] if len(VERSION.split('.')) > 2 else '0'};

// Chemins standards
constexpr const char* DEFAULT_REGISTRY_URL = "https://gsql-badge.onrender.com";
constexpr const char* DEFAULT_API_VERSION = "v5.2";
constexpr const char* LOCAL_LIB_PATH = "/usr/local/lib/goscript";
constexpr const char* CACHE_PATH = "/var/cache/gpm";
constexpr const char* CONFIG_PATH = "/etc/gpm";
constexpr const char* USER_CONFIG_PATH = "~/.config/gpm";

// Types de base
using String = std::string;
using StringView = std::string_view;
using Path = std::filesystem::path;
using Json = nlohmann::json; // Forward declaration

// Couleurs ANSI
namespace Colors {{
    constexpr const char* RESET   = "\\033[0m";
    constexpr const char* RED     = "\\033[31m";
    constexpr const char* GREEN   = "\\033[32m";
    constexpr const char* YELLOW  = "\\033[33m";
    constexpr const char* BLUE    = "\\033[34m";
    constexpr const char* MAGENTA = "\\033[35m";
    constexpr const char* CYAN    = "\\033[36m";
    constexpr const char* WHITE   = "\\033[37m";
    constexpr const char* BOLD    = "\\033[1m";
    constexpr const char* DIM     = "\\033[2m";
    constexpr const char* ITALIC  = "\\033[3m";
    constexpr const char* UNDERLINE = "\\033[4m";
}}

// ============================================================================
// STRUCTURES DE DONNÉES
// ============================================================================

// Information d'un paquet
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
    String updated_at;
    std::vector<String> dependencies;
    std::vector<String> tags;
    bool is_public = true;
}};

// Résultat d'une opération
enum class ResultCode {{
    SUCCESS = 0,
    ERROR = 1,
    NOT_FOUND = 2,
    ALREADY_EXISTS = 3,
    PERMISSION_DENIED = 4,
    NETWORK_ERROR = 5,
    INVALID_PACKAGE = 6,
    DEPENDENCY_ERROR = 7,
    CHECKSUM_ERROR = 8,
    EXTRACTION_ERROR = 9,
    CONFIG_ERROR = 10,
    AUTH_ERROR = 11,
    TIMEOUT = 12
}};

struct OperationResult {{
    ResultCode code = ResultCode::SUCCESS;
    String message;
    std::optional<String> data;
    
    bool is_success() const {{ return code == ResultCode::SUCCESS; }}
    bool is_error() const {{ return code != ResultCode::SUCCESS; }}
}};

// Configuration utilisateur
struct UserConfig {{
    String username;
    String token;
    String api_endpoint{{DEFAULT_REGISTRY_URL}};
    String api_version{{DEFAULT_API_VERSION}};
    int timeout_seconds = 30;
    int retry_count = 3;
    bool verify_ssl = true;
    bool auto_update = true;
    String default_arch = "x86_64";
    String default_release = "r0";
    std::vector<String> additional_repos;
}};

// ============================================================================
// FONCTIONS UTILITAIRES
// ============================================================================

namespace Utils {{

// Couleurs
inline String colored(const String& text, const char* color) {{
    return String(color) + text + Colors::RESET;
}}

inline String bold(const String& text) {{ return colored(text, Colors::BOLD); }}
inline String red(const String& text) {{ return colored(text, Colors::RED); }}
inline String green(const String& text) {{ return colored(text, Colors::GREEN); }}
inline String yellow(const String& text) {{ return colored(text, Colors::YELLOW); }}
inline String blue(const String& text) {{ return colored(text, Colors::BLUE); }}
inline String cyan(const String& text) {{ return colored(text, Colors::CYAN); }}

// Logging
enum class LogLevel {{ DEBUG, INFO, WARN, ERROR, FATAL }};

void log(LogLevel level, const String& message);
void info(const String& msg);
void warn(const String& msg);
void error(const String& msg);
void debug(const String& msg);
void fatal(const String& msg);

// Bannière
void print_banner();
void print_version();
void print_help();

// Système de fichiers
bool file_exists(const Path& path);
bool directory_exists(const Path& path);
bool create_directory(const Path& path);
bool remove_file(const Path& path);
bool remove_directory(const Path& path);
String read_file(const Path& path);
bool write_file(const Path& path, const String& content);
String get_home_directory();
String get_current_directory();
Path get_config_path();
Path get_cache_path();
Path get_lib_path();

// Hash
String sha256(const String& data);
String sha256_file(const Path& path);

// Compression
bool extract_tarbool(const Path& archive, const Path& dest);
bool create_tarbool(const Path& source, const Path& dest);

// Réseau
String http_get(const String& url, const std::map<String, String>& headers = {{}});
String http_post(const String& url, const String& body, const std::map<String, String>& headers = {{}});
bool download_file(const String& url, const Path& dest);

// JSON
// (nécessite nlohmann/json.hpp)

}} // namespace Utils

// ============================================================================
// MACROS UTILES
// ============================================================================

#define GPM_UNUSED(x) (void)(x)
#define GPM_STRINGIFY(x) #x
#define GPM_CONCAT(a, b) a##b

#define GPM_ASSERT(condition, message) \\
    do {{ \\
        if (!(condition)) {{ \\
            Utils::fatal(String("ASSERTION FAILED: ") + message); \\
            std::exit(1); \\
        }} \\
    }} while(0)

}} // namespace gpm

{guard_end}
"""

def generate_utils_cpp() -> str:
    """Génère gpm/_utils/utils.cpp - Utilitaires."""
    return f"""{generate_license_header()}

#include "../common.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

namespace gpm {{ namespace Utils {{

// ============================================================================
// LOGGING
// ============================================================================

static LogLevel current_log_level = LogLevel::INFO;

void log(LogLevel level, const String& message) {{
    if (level < current_log_level) return;
    
    const char* prefix;
    const char* color;
    
    switch (level) {{
        case LogLevel::DEBUG: prefix = "[DEBUG]"; color = Colors::DIM; break;
        case LogLevel::INFO:  prefix = "[INFO]";  color = Colors::BLUE; break;
        case LogLevel::WARN:  prefix = "[WARN]";  color = Colors::YELLOW; break;
        case LogLevel::ERROR: prefix = "[ERROR]"; color = Colors::RED; break;
        case LogLevel::FATAL: prefix = "[FATAL]"; color = Colors::RED; break;
        default:              prefix = "[]";      color = Colors::WHITE; break;
    }}
    
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    char time_buf[32];
    std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    
    std::cerr << Colors::DIM << time_buf << Colors::RESET << " "
              << color << prefix << Colors::RESET << " "
              << message << std::endl;
}}

void info(const String& msg)  {{ log(LogLevel::INFO, msg); }}
void warn(const String& msg)  {{ log(LogLevel::WARN, msg); }}
void error(const String& msg) {{ log(LogLevel::ERROR, msg); }}
void debug(const String& msg) {{ log(LogLevel::DEBUG, msg); }}
void fatal(const String& msg) {{ log(LogLevel::FATAL, msg); }}

// ============================================================================
// BANNIÈRE
// ============================================================================

void print_banner() {{
    std::cout << R"(
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║     ██████╗ ██████╗ ███╗   ███╗                                 ║
║    ██╔════╝ ██╔══██╗████╗ ████║                                 ║
║    ██║  ███╗██████╔╝██╔████╔██║                                 ║
║    ██║   ██║██╔═══╝ ██║╚██╔╝██║                                 ║
║    ╚██████╔╝██║     ██║ ╚═╝ ██║                                 ║
║     ╚═════╝ ╚═╝     ╚═╝     ╚═╝                                 ║
║                                                                  ║
║    Goscript Package Manager v{VERSION}                              ║
║    Copyright (c) {YEAR} {AUTHOR}                       ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝
)" << std::endl;
}}

void print_version() {{
    std::cout << "GPM v{VERSION}" << std::endl;
    std::cout << "Copyright (c) {YEAR} {AUTHOR}" << std::endl;
    std::cout << "Compilé le " << __DATE__ << " " << __TIME__ << std::endl;
}}

void print_help() {{
    std::cout << blue(bold("GPM (Goscript Package Manager) v{VERSION}")) << std::endl;
    std::cout << std::endl;
    std::cout << bold("Usage:") << std::endl;
    std::cout << "  gpm [commande] [options...]" << std::endl;
    std::cout << std::endl;
    std::cout << bold("Commandes:") << std::endl;
    std::cout << "  " << green("install") << " <paquet>    - Installer un paquet" << std::endl;
    std::cout << "  " << green("remove") << " <paquet>     - Supprimer un paquet" << std::endl;
    std::cout << "  " << green("update") << "              - Mettre à jour tous les paquets" << std::endl;
    std::cout << "  " << green("search") << " <mot-clé>  - Rechercher un paquet" << std::endl;
    std::cout << "  " << green("list") << "               - Lister les paquets installés" << std::endl;
    std::cout << "  " << green("info") << " <paquet>     - Afficher les infos d'un paquet" << std::endl;
    std::cout << "  " << green("login") << "              - Se connecter au registre" << std::endl;
    std::cout << "  " << green("publish") << "            - Publier un paquet" << std::endl;
    std::cout << "  " << green("config") << "             - Gérer la configuration" << std::endl;
    std::cout << "  " << green("version") << "            - Afficher la version" << std::endl;
    std::cout << "  " << green("help") << "               - Afficher cette aide" << std::endl;
    std::cout << std::endl;
    std::cout << bold("Options globales:") << std::endl;
    std::cout << "  --debug        - Mode debug" << std::endl;
    std::cout << "  --quiet        - Mode silencieux" << std::endl;
    std::cout << "  --no-color     - Désactiver les couleurs" << std::endl;
    std::cout << "  --config <fichier> - Fichier de configuration" << std::endl;
    std::cout << std::endl;
    std::cout << yellow("Documentation: https://github.com/gopu-inc/gpm") << std::endl;
}}

// ============================================================================
// SYSTÈME DE FICHIERS
// ============================================================================

bool file_exists(const Path& path) {{
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}}

bool directory_exists(const Path& path) {{
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}}

bool create_directory(const Path& path) {{
    std::error_code ec;
    std::filesystem::create_directories(path, ec);
    return !ec;
}}

bool remove_file(const Path& path) {{
    std::error_code ec;
    return std::filesystem::remove(path, ec);
}}

bool remove_directory(const Path& path) {{
    std::error_code ec;
    std::filesystem::remove_all(path, ec);
    return !ec;
}}

String read_file(const Path& path) {{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {{
        error("Impossible d'ouvrir le fichier: " + path.string());
        return "";
    }}
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}}

bool write_file(const Path& path, const String& content) {{
    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {{
        error("Impossible d'écrire le fichier: " + path.string());
        return false;
    }}
    file << content;
    return true;
}}

String get_home_directory() {{
    const char* home = std::getenv("HOME");
    if (home) return String(home);
    
    struct passwd* pw = getpwuid(getuid());
    if (pw) return String(pw->pw_dir);
    
    return "/root";
}}

String get_current_directory() {{
    return std::filesystem::current_path().string();
}}

Path get_config_path() {{
    String home = get_home_directory();
    Path config = Path(home) / ".config" / "gpm";
    create_directory(config);
    return config;
}}

Path get_cache_path() {{
    Path cache = CACHE_PATH;
    create_directory(cache);
    return cache;
}}

Path get_lib_path() {{
    Path lib = LOCAL_LIB_PATH;
    create_directory(lib);
    return lib;
}}

// ============================================================================
// HASH
// ============================================================================

String sha256(const String& data) {{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {{
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }}
    return ss.str();
}}

String sha256_file(const Path& path) {{
    String content = read_file(path);
    if (content.empty()) {{
        error("Impossible de calculer le hash du fichier: " + path.string());
        return "";
    }}
    return sha256(content);
}}

// ============================================================================
// COMPRESSION
// ============================================================================

bool extract_tarbool(const Path& archive, const Path& dest) {{
    create_directory(dest);
    
    String cmd = "tar -xzf \"" + archive.string() + "\" -C \"" + dest.string() + "\" 2>&1";
    
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {{
        error("Échec de l'extraction: " + archive.string());
        return false;
    }}
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {{
        debug("tar: " + String(buffer));
    }}
    
    int status = pclose(pipe);
    if (status != 0) {{
        error("Extraction échouée avec le code: " + std::to_string(status));
        return false;
    }}
    
    return true;
}}

bool create_tarbool(const Path& source, const Path& dest) {{
    String cmd = "tar -czf \"" + dest.string() + "\" -C \"" 
               + source.parent_path().string() + "\" \"" 
               + source.filename().string() + "\" 2>&1";
    
    int status = std::system(cmd.c_str());
    return status == 0;
}}

}} // namespace Utils
}} // namespace gpm
"""

def generate_install_cpp() -> str:
    """Génère gpm/_install/installer.cpp - Gestionnaire d'installation."""
    return f"""{generate_license_header()}

#include "../common.h"
#include <curl/curl.h>
#include <thread>
#include <atomic>
#include <iomanip>

namespace gpm {{

// ============================================================================
// INSTALLATEUR DE PAQUETS
// ============================================================================

class PackageInstaller {{
public:
    PackageInstaller() = default;
    ~PackageInstaller() = default;
    
    // Installation d'un paquet
    OperationResult install(const String& package_name, const String& version = "latest") {{
        Utils::info("Installation de: " + Utils::bold(package_name) + "@" + version);
        
        // 1. Résoudre la version
        String resolved_version = resolve_version(package_name, version);
        if (resolved_version.empty()) {{
            return {{ResultCode::NOT_FOUND, "Paquet introuvable: " + package_name}};
        }}
        
        // 2. Vérifier si déjà installé
        if (is_installed(package_name, resolved_version)) {{
            return {{ResultCode::ALREADY_EXISTS, "Paquet déjà installé: " + package_name + "@" + resolved_version}};
        }}
        
        // 3. Télécharger les métadonnées
        auto metadata = fetch_metadata(package_name, resolved_version);
        if (!metadata.has_value()) {{
            return {{ResultCode::NETWORK_ERROR, "Impossible de récupérer les métadonnées"}};
        }}
        
        // 4. Résoudre les dépendances
        auto deps_result = resolve_dependencies(metadata.value());
        if (!deps_result.is_success()) {{
            return deps_result;
        }}
        
        // 5. Télécharger le paquet
        auto download_result = download_package(package_name, resolved_version);
        if (!download_result.is_success()) {{
            return download_result;
        }}
        
        // 6. Vérifier l'intégrité
        auto verify_result = verify_package(download_result.data.value(), metadata->sha256);
        if (!verify_result.is_success()) {{
            return verify_result;
        }}
        
        // 7. Extraire
        auto extract_result = extract_package(download_result.data.value(), package_name);
        if (!extract_result.is_success()) {{
            return extract_result;
        }}
        
        // 8. Configurer les liens
        auto link_result = configure_links(package_name, metadata.value());
        if (!link_result.is_success()) {{
            // Rollback
            uninstall(package_name);
            return link_result;
        }}
        
        // 9. Enregistrer dans la base de données
        register_installation(package_name, resolved_version, metadata.value());
        
        Utils::info(Utils::green("✅ " + package_name + "@" + resolved_version + " installé avec succès !"));
        return {{ResultCode::SUCCESS, "Installé avec succès"}};
    }}
    
    // Désinstallation
    OperationResult uninstall(const String& package_name) {{
        Utils::info("Désinstallation de: " + Utils::bold(package_name));
        
        Path lib_path = Utils::get_lib_path() / package_name;
        
        if (!Utils::directory_exists(lib_path)) {{
            return {{ResultCode::NOT_FOUND, "Paquet non trouvé: " + package_name}};
        }}
        
        // Sauvegarder avant suppression (rollback)
        Path backup_path = Utils::get_cache_path() / "backup" / package_name;
        Utils::create_directory(backup_path.parent_path());
        std::filesystem::rename(lib_path, backup_path);
        
        // Supprimer de la base de données
        unregister_installation(package_name);
        
        Utils::info(Utils::green("✅ " + package_name + " désinstallé avec succès !"));
        return {{ResultCode::SUCCESS, "Désinstallé avec succès"}};
    }}
    
    // Mise à jour
    OperationResult update(const String& package_name) {{
        Utils::info("Mise à jour de: " + Utils::bold(package_name));
        
        auto current = get_installed_version(package_name);
        if (!current.has_value()) {{
            return {{ResultCode::NOT_FOUND, "Paquet non installé: " + package_name}};
        }}
        
        auto latest = resolve_version(package_name, "latest");
        if (latest == current.value()) {{
            return {{ResultCode::ALREADY_EXISTS, "Paquet déjà à jour"}};
        }}
        
        // Installer la nouvelle version (écrase l'ancienne)
        return install(package_name, latest);
    }}
    
    // Mise à jour de tous les paquets
    OperationResult update_all() {{
        Utils::info("Mise à jour de tous les paquets...");
        
        auto installed = get_installed_packages();
        int success = 0;
        int failed = 0;
        
        for (const auto& pkg : installed) {{
            auto result = update(pkg);
            if (result.is_success()) {{
                success++;
            }} else {{
                failed++;
                Utils::warn("Échec de mise à jour: " + pkg);
            }}
        }}
        
        Utils::info(Utils::green("✅ " + std::to_string(success) + " mis à jour, " 
                   + Utils::red(std::to_string(failed)) + " échecs"));
        
        return {{ResultCode::SUCCESS, "Mise à jour terminée"}};
    }}

private:
    String resolve_version(const String& name, const String& version) {{
        // TODO: Implémenter la résolution de version via l'API
        if (version == "latest") {{
            return fetch_latest_version(name);
        }}
        return version;
    }}
    
    String fetch_latest_version(const String& name) {{
        String url = String(DEFAULT_REGISTRY_URL) + "/api/" + DEFAULT_API_VERSION 
                   + "/package/" + name + "/latest";
        String response = Utils::http_get(url);
        
        // Parser la réponse JSON pour extraire la version
        // Pour l'instant, retourne une version par défaut
        return "1.0.0";
    }}
    
    bool is_installed(const String& name, const String& version) {{
        Path pkg_path = Utils::get_lib_path() / name;
        Path version_file = pkg_path / "VERSION";
        
        if (!Utils::file_exists(version_file)) return false;
        
        String installed_version = Utils::read_file(version_file);
        installed_version.erase(
            std::remove(installed_version.begin(), installed_version.end(), '\\n'),
            installed_version.end()
        );
        
        return installed_version == version;
    }}
    
    std::optional<PackageInfo> fetch_metadata(const String& name, const String& version) {{
        String url = String(DEFAULT_REGISTRY_URL) + "/api/" + DEFAULT_API_VERSION 
                   + "/package/" + name;
        if (!version.empty()) {{
            url += "?version=" + version;
        }}
        
        String response = Utils::http_get(url);
        if (response.empty()) return std::nullopt;
        
        // Parser le JSON
        // TODO: Implémenter le parsing JSON complet
        PackageInfo info;
        info.name = name;
        info.version = version;
        return info;
    }}
    
    OperationResult resolve_dependencies(const PackageInfo& pkg) {{
        for (const auto& dep : pkg.dependencies) {{
            // Vérifier si la dépendance est installée
            if (!is_installed(dep, "")) {{
                Utils::info("Résolution de la dépendance: " + dep);
                auto result = install(dep);
                if (!result.is_success()) {{
                    return {{ResultCode::DEPENDENCY_ERROR, 
                            "Impossible de résoudre la dépendance: " + dep}};
                }}
            }}
        }}
        return {{ResultCode::SUCCESS}};
    }}
    
    OperationResult download_package(const String& name, const String& version) {{
        String filename = name + "-" + version + "-r0-x86_64.tar.bool";
        String url = String(DEFAULT_REGISTRY_URL) + "/package/download/public/"
                   + name + "/" + version + "/r0/x86_64";
        
        Path dest = Utils::get_cache_path() / "downloads" / filename;
        Utils::create_directory(dest.parent_path());
        
        if (Utils::download_file(url, dest)) {{
            return {{ResultCode::SUCCESS, "Téléchargé", dest.string()}};
        }}
        
        return {{ResultCode::NETWORK_ERROR, "Échec du téléchargement"}};
    }}
    
    OperationResult verify_package(const String& file_path, const String& expected_hash) {{
        if (expected_hash.empty()) {{
            return {{ResultCode::SUCCESS, "Vérification ignorée (pas de hash)"}};
        }}
        
        String actual_hash = Utils::sha256_file(file_path);
        if (actual_hash != expected_hash) {{
            Utils::error("Hash invalide !");
            Utils::error("  Attendu:  " + expected_hash);
            Utils::error("  Obtenu:   " + actual_hash);
            return {{ResultCode::CHECKSUM_ERROR, "Échec de la vérification d'intégrité"}};
        }}
        
        Utils::debug("Hash vérifié avec succès");
        return {{ResultCode::SUCCESS}};
    }}
    
    OperationResult extract_package(const String& archive_path, const String& name) {{
        Path dest = Utils::get_lib_path() / name;
        
        // Nettoyer l'ancienne installation si elle existe
        if (Utils::directory_exists(dest)) {{
            Utils::remove_directory(dest);
        }}
        
        if (Utils::extract_tarbool(archive_path, dest)) {{
            // Écrire le fichier VERSION
            Utils::write_file(dest / "VERSION", "1.0.0");
            return {{ResultCode::SUCCESS}};
        }}
        
        return {{ResultCode::EXTRACTION_ERROR, "Échec de l'extraction"}};
    }}
    
    OperationResult configure_links(const String& name, const PackageInfo& pkg) {{
        // Créer les liens symboliques nécessaires
        Path lib_path = Utils::get_lib_path() / name;
        Path bin_path = lib_path / "bin";
        
        if (Utils::directory_exists(bin_path)) {{
            for (const auto& entry : std::filesystem::directory_iterator(bin_path)) {{
                if (entry.is_regular_file()) {{
                    Path target = Path("/usr/local/bin") / entry.path().filename();
                    std::filesystem::create_symlink(entry.path(), target);
                    Utils::debug("Lien créé: " + target.string());
                }}
            }}
        }}
        
        return {{ResultCode::SUCCESS}};
    }}
    
    void register_installation(const String& name, const String& version, const PackageInfo& pkg) {{
        Path db_path = Utils::get_config_path() / "installed.json";
        
        // TODO: Implémenter le JSON pour la base de données
        String entry = name + " " + version + " " + std::to_string(std::time(nullptr));
        String existing = Utils::read_file(db_path);
        Utils::write_file(db_path, existing + entry + "\\n");
    }}
    
    void unregister_installation(const String& name) {{
        Path db_path = Utils::get_config_path() / "installed.json";
        String content = Utils::read_file(db_path);
        
        // Supprimer la ligne correspondante
        std::istringstream iss(content);
        std::ostringstream oss;
        String line;
        while (std::getline(iss, line)) {{
            if (line.find(name + " ") != 0) {{
                oss << line << "\\n";
            }}
        }}
        
        Utils::write_file(db_path, oss.str());
    }}
    
    std::optional<String> get_installed_version(const String& name) {{
        Path version_file = Utils::get_lib_path() / name / "VERSION";
        if (!Utils::file_exists(version_file)) {{
            return std::nullopt;
        }}
        
        String version = Utils::read_file(version_file);
        version.erase(std::remove(version.begin(), version.end(), '\\n'), version.end());
        return version;
    }}
    
    std::vector<String> get_installed_packages() {{
        std::vector<String> packages;
        Path lib_path = Utils::get_lib_path();
        
        if (Utils::directory_exists(lib_path)) {{
            for (const auto& entry : std::filesystem::directory_iterator(lib_path)) {{
                if (entry.is_directory()) {{
                    packages.push_back(entry.path().filename().string());
                }}
            }}
        }}
        
        return packages;
    }}
}};

// Instance globale
static PackageInstaller installer;

// ============================================================================
// INTERFACE PUBLIQUE
// ============================================================================

OperationResult install_package(const String& name, const String& version) {{
    return installer.install(name, version);
}}

OperationResult uninstall_package(const String& name) {{
    return installer.uninstall(name);
}}

OperationResult update_package(const String& name) {{
    return installer.update(name);
}}

OperationResult update_all_packages() {{
    return installer.update_all();
}}

}} // namespace gpm
"""

def generate_protocol_cpp() -> str:
    """Génère gpm/_protocol/protocol.cpp - Protocole réseau."""
    return f"""{generate_license_header()}

#include "../common.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace gpm {{ namespace Protocol {{

// ============================================================================
// CLIENT API
// ============================================================================

class APIClient {{
public:
    APIClient(const String& base_url = DEFAULT_REGISTRY_URL) 
        : base_url(base_url) {{
        curl_global_init(CURL_GLOBAL_ALL);
    }}
    
    ~APIClient() {{
        curl_global_cleanup();
    }}
    
    // ========================================================================
    // MÉTHODES API
    // ========================================================================
    
    // Recherche de paquets
    std::vector<PackageInfo> search_packages(const String& query) {{
        String url = build_url("/api/" + String(DEFAULT_API_VERSION) + "/package/search?q=" + url_encode(query));
        auto response = get(url);
        
        std::vector<PackageInfo> results;
        if (response.contains("results")) {{
            for (const auto& item : response["results"]) {{
                PackageInfo pkg;
                pkg.name = item.value("name", "");
                pkg.version = item.value("version", "");
                pkg.author = item.value("author", "");
                pkg.downloads = item.value("downloads", 0);
                pkg.description = item.value("description", "");
                results.push_back(pkg);
            }}
        }}
        return results;
    }}
    
    // Détails d'un paquet
    std::optional<PackageInfo> get_package_details(const String& name, const String& version = "") {{
        String url = build_url("/api/" + String(DEFAULT_API_VERSION) + "/package/" + name);
        if (!version.empty()) {{
            url += "?version=" + url_encode(version);
        }}
        
        auto response = get(url);
        if (!response.contains("package")) return std::nullopt;
        
        auto& p = response["package"];
        PackageInfo pkg;
        pkg.name = p.value("name", "");
        pkg.version = p.value("version", "");
        pkg.release = p.value("release", "r0");
        pkg.arch = p.value("arch", "x86_64");
        pkg.scope = p.value("scope", "public");
        pkg.author = p.value("author", "");
        pkg.sha256 = p.value("sha256", "");
        pkg.size = p.value("size", 0);
        pkg.downloads = p.value("downloads", 0);
        pkg.description = p.value("description", "");
        pkg.created_at = p.value("created_at", "");
        
        return pkg;
    }}
    
    // Authentification
    OperationResult login(const String& username, const String& password) {{
        json body;
        body["username"] = username;
        body["password"] = password;
        
        String url = build_url("/v5.2/auth/login");
        auto response = post(url, body);
        
        if (response.contains("token")) {{
            auth_token = response["token"];
            return {{ResultCode::SUCCESS, "Connecté avec succès", auth_token}};
        }}
        
        return {{ResultCode::AUTH_ERROR, response.value("error", "Erreur d'authentification")}};
    }}
    
    // Enregistrement
    OperationResult register_user(const String& username, const String& email, const String& password) {{
        json body;
        body["username"] = username;
        body["email"] = email;
        body["password"] = password;
        
        String url = build_url("/v5.2/auth/register");
        auto response = post(url, body);
        
        if (response.contains("token")) {{
            auth_token = response["token"];
            return {{ResultCode::SUCCESS, "Enregistré avec succès", auth_token}};
        }}
        
        return {{ResultCode::ERROR, response.value("error", "Erreur d'enregistrement")}};
    }}
    
    // Publication d'un paquet
    OperationResult publish_package(const String& name, const Path& archive_path, const PackageInfo& info) {{
        String url = build_url("/v5.2/package/upload/" + info.scope + "/" + name);
        
        // Upload multipart avec curl
        CURL* curl = curl_easy_init();
        if (!curl) {{
            return {{ResultCode::NETWORK_ERROR, "Impossible d'initialiser CURL"}};
        }}
        
        curl_mime* form = curl_mime_init(curl);
        curl_mimepart* field = curl_mime_addpart(form);
        curl_mime_name(field, "file");
        curl_mime_filedata(field, archive_path.c_str());
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "version");
        curl_mime_data(field, info.version.c_str(), CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "release");
        curl_mime_data(field, info.release.c_str(), CURL_ZERO_TERMINATED);
        
        field = curl_mime_addpart(form);
        curl_mime_name(field, "arch");
        curl_mime_data(field, info.arch.c_str(), CURL_ZERO_TERMINATED);
        
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + auth_token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        String response_data;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        
        CURLcode res = curl_easy_perform(curl);
        
        curl_mime_free(form);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) {{
            return {{ResultCode::NETWORK_ERROR, curl_easy_strerror(res)}};
        }}
        
        auto response = json::parse(response_data);
        if (response.contains("success") && response["success"].get<bool>()) {{
            return {{ResultCode::SUCCESS, "Paquet publié avec succès"}};
        }}
        
        return {{ResultCode::ERROR, response.value("error", "Erreur de publication")}};
    }}

private:
    String base_url;
    String auth_token;
    
    String build_url(const String& path) {{
        if (path.starts_with("http")) return path;
        return base_url + path;
    }}
    
    String url_encode(const String& str) {{
        CURL* curl = curl_easy_init();
        if (!curl) return str;
        char* encoded = curl_easy_escape(curl, str.c_str(), str.length());
        String result(encoded);
        curl_free(encoded);
        curl_easy_cleanup(curl);
        return result;
    }}
    
    json get(const String& url) {{
        String response = Utils::http_get(url, get_auth_headers());
        if (response.empty()) return json::object();
        
        try {{
            return json::parse(response);
        }} catch (...) {{
            return json::object();
        }}
    }}
    
    json post(const String& url, const json& body) {{
        String response = Utils::http_post(url, body.dump(), get_auth_headers());
        if (response.empty()) return json::object();
        
        try {{
            return json::parse(response);
        }} catch (...) {{
            return json::object();
        }}
    }}
    
    std::map<String, String> get_auth_headers() {{
        std::map<String, String> headers;
        headers["Content-Type"] = "application/json";
        if (!auth_token.empty()) {{
            headers["Authorization"] = "Bearer " + auth_token;
        }}
        return headers;
    }}
    
    static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {{
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }}
}};

// Instance globale
static APIClient client;

// ============================================================================
// INTERFACE PUBLIQUE
// ============================================================================

std::vector<PackageInfo> search(const String& query) {{
    return client.search_packages(query);
}}

std::optional<PackageInfo> get_details(const String& name, const String& version) {{
    return client.get_package_details(name, version);
}}

OperationResult login(const String& user, const String& pass) {{
    return client.login(user, pass);
}}

OperationResult register_user(const String& user, const String& email, const String& pass) {{
    return client.register_user(user, email, pass);
}}

OperationResult publish(const String& name, const Path& archive, const PackageInfo& info) {{
    return client.publish_package(name, archive, info);
}}

}} // namespace Protocol
}} // namespace gpm
"""

def generate_main_cpp() -> str:
    """Génère gpm/main.cpp - Point d'entrée principal."""
    return f"""{generate_license_header()}

#include "common.h"
#include "_utils/utils.cpp"
#include "_install/installer.cpp"
#include "_protocol/protocol.cpp"
#include "_download/downloader.cpp"
#include "_login/auth.cpp"
#include "_publish/publisher.cpp"
#include "_security/security.cpp"
#include "_macro/macro.cpp"
#include "_config/config.cpp"
#include "_cache/cache.cpp"

using namespace gpm;

// ============================================================================
// GESTIONNAIRE DE COMMANDES
// ============================================================================

class CommandHandler {{
public:
    CommandHandler(int argc, char** argv) 
        : argc(argc), argv(argv) {{
        parse_global_options();
    }}
    
    int run() {{
        if (show_help) {{
            Utils::print_help();
            return 0;
        }}
        
        if (show_version) {{
            Utils::print_version();
            return 0;
        }}
        
        if (command.empty()) {{
            Utils::print_banner();
            std::cout << Utils::yellow("Utilisez 'gpm --help' pour voir les commandes disponibles.") << std::endl;
            return 0;
        }}
        
        return execute_command();
    }}

private:
    int argc;
    char** argv;
    String command;
    std::vector<String> args;
    bool show_help = false;
    bool show_version = false;
    bool debug_mode = false;
    bool quiet_mode = false;
    
    void parse_global_options() {{
        for (int i = 1; i < argc; i++) {{
            String arg = argv[i];
            
            if (arg == "--help" || arg == "-h") {{
                show_help = true;
            }} else if (arg == "--version" || arg == "-v") {{
                show_version = true;
            }} else if (arg == "--debug" || arg == "-d") {{
                debug_mode = true;
            }} else if (arg == "--quiet" || arg == "-q") {{
                quiet_mode = true;
            }} else if (command.empty()) {{
                command = arg;
            }} else {{
                args.push_back(arg);
            }}
        }}
    }}
    
    int execute_command() {{
        if (command == "install")       return cmd_install();
        if (command == "remove")        return cmd_remove();
        if (command == "update")        return cmd_update();
        if (command == "search")        return cmd_search();
        if (command == "list")          return cmd_list();
        if (command == "info")          return cmd_info();
        if (command == "login")         return cmd_login();
        if (command == "publish")       return cmd_publish();
        if (command == "config")        return cmd_config();
        if (command == "version")       {{ Utils::print_version(); return 0; }}
        if (command == "help")          {{ Utils::print_help(); return 0; }}
        
        Utils::error("Commande inconnue: " + command);
        Utils::info("Utilisez 'gpm --help' pour voir les commandes disponibles.");
        return 1;
    }}
    
    // ========================================================================
    // COMMANDES
    // ========================================================================
    
    int cmd_install() {{
        if (args.empty()) {{
            Utils::error("Usage: gpm install <paquet> [version]");
            return 1;
        }}
        
        String name = args[0];
        String version = args.size() > 1 ? args[1] : "latest";
        
        auto result = install_package(name, version);
        return result.is_success() ? 0 : 1;
    }}
    
    int cmd_remove() {{
        if (args.empty()) {{
            Utils::error("Usage: gpm remove <paquet>");
            return 1;
        }}
        
        auto result = uninstall_package(args[0]);
        return result.is_success() ? 0 : 1;
    }}
    
    int cmd_update() {{
        if (args.empty()) {{
            auto result = update_all_packages();
            return result.is_success() ? 0 : 1;
        }}
        
        auto result = update_package(args[0]);
        return result.is_success() ? 0 : 1;
    }}
    
    int cmd_search() {{
        if (args.empty()) {{
            Utils::error("Usage: gpm search <mot-clé>");
            return 1;
        }}
        
        String query;
        for (size_t i = 0; i < args.size(); i++) {{
            if (i > 0) query += " ";
            query += args[i];
        }}
        
        auto results = Protocol::search(query);
        
        if (results.empty()) {{
            std::cout << Utils::yellow("Aucun résultat pour: " + query) << std::endl;
            return 0;
        }}
        
        std::cout << Utils::bold("Résultats pour \"" + query + "\":") << std::endl;
        std::cout << std::endl;
        
        for (const auto& pkg : results) {{
            std::cout << Utils::green("  " + pkg.name) 
                      << Utils::dim(" @" + pkg.version)
                      << " - " << pkg.description.substr(0, 50) << std::endl;
            std::cout << Utils::dim("    Par: " + pkg.author + " | " 
                      + std::to_string(pkg.downloads) + " téléchargements") << std::endl;
        }}
        
        return 0;
    }}
    
    int cmd_list() {{
        Path lib_path = Utils::get_lib_path();
        
        if (!Utils::directory_exists(lib_path)) {{
            std::cout << Utils::yellow("Aucun paquet installé.") << std::endl;
            return 0;
        }}
        
        std::cout << Utils::bold("Paquets installés:") << std::endl;
        std::cout << std::endl;
        
        int count = 0;
        for (const auto& entry : std::filesystem::directory_iterator(lib_path)) {{
            if (entry.is_directory()) {{
                String name = entry.path().filename().string();
                Path version_file = entry.path() / "VERSION";
                String version = "inconnue";
                
                if (Utils::file_exists(version_file)) {{
                    version = Utils::read_file(version_file);
                    version.erase(std::remove(version.begin(), version.end(), '\\n'), version.end());
                }}
                
                std::cout << "  " << Utils::green(name) 
                          << Utils::dim(" @" + version) << std::endl;
                count++;
            }}
        }}
        
        std::cout << std::endl;
        std::cout << Utils::dim(std::to_string(count) + " paquet(s) installé(s)") << std::endl;
        
        return 0;
    }}
    
    int cmd_info() {{
        if (args.empty()) {{
            Utils::error("Usage: gpm info <paquet> [version]");
            return 1;
        }}
        
        String name = args[0];
        String version = args.size() > 1 ? args[1] : "";
        
        auto info = Protocol::get_details(name, version);
        if (!info.has_value()) {{
            Utils::error("Paquet introuvable: " + name);
            return 1;
        }}
        
        auto& pkg = info.value();
        
        std::cout << Utils::bold("Informations sur le paquet:") << std::endl;
        std::cout << std::endl;
        std::cout << "  " << Utils::bold("Nom:")        << " " << Utils::green(pkg.name) << std::endl;
        std::cout << "  " << Utils::bold("Version:")    << " " << pkg.version << std::endl;
        std::cout << "  " << Utils::bold("Auteur:")     << " " << pkg.author << std::endl;
        std::cout << "  " << Utils::bold("Architecture:") << " " << pkg.arch << std::endl;
        std::cout << "  " << Utils::bold("Release:")    << " " << pkg.release << std::endl;
        std::cout << "  " << Utils::bold("Visibilité:") << " " << (pkg.scope == "public" ? "Public" : "Privé") << std::endl;
        std::cout << "  " << Utils::bold("Taille:")     << " " << format_size(pkg.size) << std::endl;
        std::cout << "  " << Utils::bold("SHA256:")     << " " << pkg.sha256 << std::endl;
        std::cout << "  " << Utils::bold("Téléchargements:") << " " << pkg.downloads << std::endl;
        
        if (!pkg.description.empty()) {{
            std::cout << "  " << Utils::bold("Description:") << std::endl;
            std::cout << "    " << pkg.description << std::endl;
        }}
        
        if (!pkg.tags.empty()) {{
            std::cout << "  " << Utils::bold("Tags:") << " ";
            for (size_t i = 0; i < pkg.tags.size(); i++) {{
                if (i > 0) std::cout << ", ";
                std::cout << Utils::cyan(pkg.tags[i]);
            }}
            std::cout << std::endl;
        }}
        
        return 0;
    }}
    
    int cmd_login() {{
        String username, password;
        
        if (args.size() >= 2) {{
            username = args[0];
            password = args[1];
        }} else {{
            std::cout << "Nom d'utilisateur: ";
            std::getline(std::cin, username);
            
            std::cout << "Mot de passe: ";
            // TODO: Masquer le mot de passe
            std::getline(std::cin, password);
        }}
        
        auto result = Protocol::login(username, password);
        if (result.is_success()) {{
            std::cout << Utils::green("✅ Connecté avec succès !") << std::endl;
            
            // Sauvegarder le token
            if (result.data.has_value()) {{
                Config::save_auth_token(result.data.value());
            }}
            return 0;
        }}
        
        Utils::error("Échec de connexion: " + result.message);
        return 1;
    }}
    
    int cmd_publish() {{
        if (args.empty()) {{
            Utils::error("Usage: gpm publish <dossier_du_paquet>");
            return 1;
        }}
        
        String source_dir = args[0];
        
        if (!Utils::directory_exists(source_dir)) {{
            Utils::error("Dossier introuvable: " + source_dir);
            return 1;
        }}
        
        // Vérifier l'authentification
        String token = Config::get_auth_token();
        if (token.empty()) {{
            Utils::error("Non authentifié. Utilisez 'gpm login' d'abord.");
            return 1;
        }}
        
        // Lire les métadonnées
        auto metadata = Publish::read_package_metadata(source_dir);
        if (!metadata.has_value()) {{
            Utils::error("Impossible de lire les métadonnées du paquet");
            return 1;
        }}
        
        // Créer l'archive
        Path archive_path = Utils::get_cache_path() / "publish" 
                          / (metadata->name + "-" + metadata->version + ".tar.bool");
        Utils::create_directory(archive_path.parent_path());
        
        if (!Publish::create_package_archive(source_dir, archive_path)) {{
            Utils::error("Impossible de créer l'archive du paquet");
            return 1;
        }}
        
        // Publier
        auto result = Protocol::publish(metadata->name, archive_path, metadata.value());
        if (result.is_success()) {{
            std::cout << Utils::green("✅ Paquet publié avec succès !") << std::endl;
            std::cout << "   " << Utils::bold("Nom:") << " " << metadata->name << std::endl;
            std::cout << "   " << Utils::bold("Version:") << " " << metadata->version << std::endl;
            return 0;
        }}
        
        Utils::error("Échec de publication: " + result.message);
        return 1;
    }}
    
    int cmd_config() {{
        std::cout << Utils::bold("Configuration GPM:") << std::endl;
        std::cout << std::endl;
        
        Path config_path = Utils::get_config_path();
        std::cout << "  " << Utils::bold("Chemin de configuration:") << " " << config_path.string() << std::endl;
        std::cout << "  " << Utils::bold("Chemin de cache:") << " " << Utils::get_cache_path().string() << std::endl;
        std::cout << "  " << Utils::bold("Chemin des bibliothèques:") << " " << Utils::get_lib_path().string() << std::endl;
        std::cout << "  " << Utils::bold("Registre:") << " " << DEFAULT_REGISTRY_URL << std::endl;
        std::cout << "  " << Utils::bold("Version API:") << " " << DEFAULT_API_VERSION << std::endl;
        
        String token = Config::get_auth_token();
        std::cout << "  " << Utils::bold("Authentifié:") << " " 
                  << (token.empty() ? Utils::red("Non") : Utils::green("Oui")) << std::endl;
        
        return 0;
    }}
    
    // Utilitaire
    String format_size(size_t bytes) {{
        const char* units[] = {{"B", "KB", "MB", "GB", "TB"}};
        int unit_idx = 0;
        double size = bytes;
        
        while (size >= 1024 && unit_idx < 4) {{
            size /= 1024;
            unit_idx++;
        }}
        
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << size << " " << units[unit_idx];
        return ss.str();
    }}
}};

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char** argv) {{
    // Gestion des signaux
    std::signal(SIGINT, [](int) {{
        std::cout << std::endl << Utils::yellow("⏹ Interruption") << std::endl;
        std::exit(1);
    }});
    
    std::signal(SIGTERM, [](int) {{
        std::cout << std::endl << Utils::yellow("⏹ Terminaison") << std::endl;
        std::exit(1);
    }});
    
    // Initialiser les répertoires
    Utils::create_directory(Utils::get_config_path());
    Utils::create_directory(Utils::get_cache_path());
    Utils::create_directory(Utils::get_lib_path());
    
    // Exécuter la commande
    CommandHandler handler(argc, argv);
    return handler.run();
}}
"""

def generate_stub_files() -> dict:
    """Génère les fichiers stub pour les modules non encore implémentés."""
    stubs = {}
    
    # _download/downloader.cpp
    stubs["gpm/_download/downloader.cpp"] = f"""{generate_license_header()}

#include "../common.h"
#include <curl/curl.h>

namespace gpm {{ namespace Download {{

// Téléchargeur de fichiers
class Downloader {{
public:
    static bool download(const String& url, const Path& dest) {{
        // Utilise curl pour télécharger le fichier
        CURL* curl = curl_easy_init();
        if (!curl) return false;
        
        FILE* fp = fopen(dest.c_str(), "wb");
        if (!fp) {{
            curl_easy_cleanup(curl);
            return false;
        }}
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L);
        
        CURLcode res = curl_easy_perform(curl);
        
        fclose(fp);
        curl_easy_cleanup(curl);
        
        return res == CURLE_OK;
    }}

private:
    static size_t write_to_file(void* ptr, size_t size, size_t nmemb, FILE* stream) {{
        return fwrite(ptr, size, nmemb, stream);
    }}
}};

}} // namespace Download
}} // namespace gpm
"""
    
    # _login/auth.cpp
    stubs["gpm/_login/auth.cpp"] = f"""{generate_license_header()}

#include "../common.h"

namespace gpm {{ namespace Auth {{

class Authenticator {{
public:
    static bool validate_token(const String& token) {{
        // Valider le token JWT localement
        return !token.empty();
    }}
    
    static String get_current_user() {{
        // Récupérer l'utilisateur courant
        return std::getenv("USER") ? std::getenv("USER") : "unknown";
    }}
}};

}} // namespace Auth
}} // namespace gpm
"""
    
    # _publish/publisher.cpp
    stubs["gpm/_publish/publisher.cpp"] = f"""{generate_license_header()}

#include "../common.h"

namespace gpm {{ namespace Publish {{

std::optional<PackageInfo> read_package_metadata(const String& dir) {{
    Path gpmfile = Path(dir) / "Gpmfile";
    if (!Utils::file_exists(gpmfile)) {{
        Utils::error("Gpmfile introuvable dans: " + dir);
        return std::nullopt;
    }}
    
    // Parser le Gpmfile (format TOML simplifié)
    String content = Utils::read_file(gpmfile);
    
    PackageInfo info;
    info.name = "unknown";
    info.version = "0.1.0";
    info.scope = "public";
    info.release = "r0";
    info.arch = "x86_64";
    
    // TODO: Implémenter un vrai parser TOML
    
    return info;
}}

bool create_package_archive(const Path& source, const Path& dest) {{
    return Utils::create_tarbool(source, dest);
}}

}} // namespace Publish
}} // namespace gpm
"""
    
    # _security/security.cpp
    stubs["gpm/_security/security.cpp"] = f"""{generate_license_header()}

#include "../common.h"
#include <openssl/evp.h>
#include <openssl/pem.h>

namespace gpm {{ namespace Security {{

class SecurityManager {{
public:
    static String encrypt(const String& data, const String& key) {{
        // Chiffrement AES-256-GCM
        return data; // Stub
    }}
    
    static String decrypt(const String& data, const String& key) {{
        // Déchiffrement AES-256-GCM
        return data; // Stub
    }}
    
    static String generate_token() {{
        unsigned char buf[32];
        if (RAND_bytes(buf, sizeof(buf)) != 1) {{
            return "";
        }}
        
        std::stringstream ss;
        for (int i = 0; i < 32; i++) {{
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)buf[i];
        }}
        return ss.str();
    }}
}};

}} // namespace Security
}} // namespace gpm
"""
    
    # _macro/macro.cpp
    stubs["gpm/_macro/macro.cpp"] = f"""{generate_license_header()}

#include "../common.h"

namespace gpm {{ namespace Macro {{

class MacroExpander {{
public:
    static String expand(const String& input) {{
        // Expansion de macros dans les commandes
        String result = input;
        
        // Substituer les variables d'environnement
        size_t pos = 0;
        while ((pos = result.find("${{", pos)) != String::npos) {{
            size_t end = result.find("}}", pos);
            if (end == String::npos) break;
            
            String var_name = result.substr(pos + 2, end - pos - 2);
            const char* var_value = std::getenv(var_name.c_str());
            
            result.replace(pos, end - pos + 2, var_value ? var_value : "");
            pos += (var_value ? strlen(var_value) : 0);
        }}
        
        return result;
    }}
}};

}} // namespace Macro
}} // namespace gpm
"""
    
    # _config/config.cpp
    stubs["gpm/_config/config.cpp"] = f"""{generate_license_header()}

#include "../common.h"

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
    
    # _cache/cache.cpp
    stubs["gpm/_cache/cache.cpp"] = f"""{generate_license_header()}

#include "../common.h"

namespace gpm {{ namespace Cache {{

class CacheManager {{
public:
    static Path get_cache_path() {{
        return Utils::get_cache_path();
    }}
    
    static bool clear() {{
        Path cache = Utils::get_cache_path();
        return Utils::remove_directory(cache);
    }}
    
    static size_t get_size() {{
        size_t total = 0;
        Path cache = Utils::get_cache_path();
        
        if (Utils::directory_exists(cache)) {{
            for (const auto& entry : std::filesystem::recursive_directory_iterator(cache)) {{
                if (entry.is_regular_file()) {{
                    total += entry.file_size();
                }}
            }}
        }}
        
        return total;
    }}
}};

}} // namespace Cache
}} // namespace gpm
"""
    
    return stubs

def generate_all() -> None:
    """Génère tous les fichiers du projet GPM."""
    print("""
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║     GPM - Goscript Package Manager Generator                     ║
║     Génération du code source complet...                         ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝
""")
    
    # Créer la structure de répertoires
    print("\n📁 Création de la structure des répertoires :")
    for directory in DIR_STRUCTURE:
        create_directory(directory)
    
    # Générer les fichiers principaux
    print("\n📄 Génération des fichiers source :")
    
    # Fichiers racine
    write_file(".gitignore", generate_gitignore())
    write_file("Makefile", generate_makefile())
    
    # Fichiers core
    write_file("gpm/common.h", generate_common_h())
    write_file("gpm/main.cpp", generate_main_cpp())
    write_file("gpm/_utils/utils.cpp", generate_utils_cpp())
    write_file("gpm/_install/installer.cpp", generate_install_cpp())
    write_file("gpm/_protocol/protocol.cpp", generate_protocol_cpp())
    
    # Fichiers stub
    stubs = generate_stub_files()
    for path, content in stubs.items():
        write_file(path, content)
    
    # Créer les fichiers d'en-tête vides
    header_files = [
        "gpm/_download/downloader.h",
        "gpm/_login/auth.h",
        "gpm/_publish/publisher.h",
        "gpm/_security/security.h",
        "gpm/_macro/macro.h",
        "gpm/_config/config.h",
        "gpm/_cache/cache.h",
        "gpm/_daemon/daemon.h",
        "gpm/_rollback/rollback.h",
        "gpm/_verify/verify.h",
        "gpm/_linker/linker.h",
        "gpm/_parser/parser.h"
    ]
    
    for header in header_files:
        guard_start, guard_end = generate_header_guard(Path(header).stem)
        content = f"""{generate_license_header()}

{guard_start}

#include "../common.h"

namespace gpm {{

// Module: {Path(header).parent.filename().string()}

}} // namespace gpm

{guard_end}
"""
        write_file(header, content)
    
    # Créer un fichier README
    readme = f"""# GPM - Goscript Package Manager

Version: {VERSION}
Copyright (c) {YEAR} {AUTHOR}

## Description

GPM est le gestionnaire de paquets officiel pour le langage Goscript.
Il permet d'installer, mettre à jour et publier des paquets Goscript.

## Installation

### Prérequis

- g++ (support C++17)
- libcurl
- OpenSSL
- zlib
- pthread
- make

### Compilation
cd gpm
make
Installation système


sudo make install

Utilisation


# Installer un paquet
gpm install <nom_du_paquet>

# Désinstaller un paquet
gpm remove <nom_du_paquet>

# Mettre à jour tous les paquets
gpm update

# Rechercher un paquet
gpm search <mot-clé>

# Lister les paquets installés
gpm list

# Afficher les informations d'un paquet
gpm info <nom_du_paquet>

# Se connecter
gpm login

# Publier un paquet
gpm publish <dossier_du_paquet>

# Afficher la configuration
gpm config

# Afficher l'aide
gpm --help

Structure du projet

gpm/
├── _utils/       # Utilitaires généraux
├── _install/     # Gestionnaire d'installation
├── _protocol/    # Protocole réseau / API
├── _download/    # Téléchargement de fichiers
├── _login/       # Authentification
├── _publish/     # Publication de paquets
├── _security/    # Sécurité / Chiffrement
├── _macro/       # Expansion de macros
├── _config/      # Configuration
├── _cache/       # Gestion du cache
├── _daemon/      # Service en arrière-plan
├── _rollback/    # Retour en arrière
├── _verify/      # Vérification d'intégrité
├── _linker/      # Gestion des liens
└── _parser/      # Analyse syntaxique

Licence

MIT License - voir le fichier LICENSE
"""
write_file("README.md", readme)


# Rendre le Makefile exécutable
make_executable("Makefile")

print(f"""


╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║  ✅ Génération terminée avec succès !                           ║
║                                                                  ║
║  📁 Projet créé dans : {os.path.abspath(PROJECT_ROOT)}/
║  📊 Fichiers générés : {len(list(Path(PROJECT_ROOT).rglob('*')))} fichiers
║                                                                  ║
║  Pour compiler :                                                ║
║    cd {PROJECT_ROOT} && make                                    ║
║                                                                  ║
║  Pour installer :                                               ║
║    cd {PROJECT_ROOT} && sudo make install                       ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝
""")

============================================================================

POINT D'ENTRÉE

============================================================================
"""

if name == "main":
# Nettoyer l'ancien projet si il existe
if os.path.exists(PROJECT_ROOT):
response = input(f"Le dossier '{PROJECT_ROOT}' existe déjà. Voulez-vous l'écraser ? (o/N) : ")
if response.lower() == 'o':
shutil.rmtree(PROJECT_ROOT)
print(f"🗑️  Ancien projet supprimé.")
else:
print("❌ Opération annulée.")
sys.exit(1)

# Générer le projet
generate_all()
