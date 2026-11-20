# Goscript — Documentation complète / Complete documentation

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)
[![Build Status](https://github.com/gopu-inc/goscript/actions/workflows/goscript-buil.yml/badge.svg)](https://github.com/gopu-inc/goscript/actions)

Français ↔ English — ce README est bilingue. Les sections FR puis EN présentent le projet, l'installation, la compilation, l'utilisation, la librairie standard, le développement et la contribution.

---

## 🇫🇷 Présentation rapide

Goscript (extension `.gjs`) est un langage de scripting moderne et léger développé par la communauté GOPU. Conçu pour l'automatisation, l'intégration système (exécution de commandes shell), et l'extension via des modules, Goscript vise un bon compromis entre expressivité et performance.

Binaire principal compilé: `gd` (généré par `make`).

Principales caractéristiques
- Typage dynamique au runtime
- Syntaxe familière (fonctions `fn`, `struct`, `impl`, `match`, `async/await`)
- Intégration système native (`sysf`, `sh`, FFI, `unsafe`)
- Gestion d'environnement (`genv`) et gestionnaire de paquets Goscript (`golem`)
- Support pour éditeurs (grammars, snippets, VSCode extension via `package.json`)

Dossier clés du dépôt
- `src/` : code C (parser, interpreter, AST)
- `lib/` : librairie standard et modules `.gjs`
- `exemples/` : scripts d'exemple
- `lib/golem/` : gestionnaire de paquets Goscript
- `grammars/`, `vim/`, `syntaxes/` : intégration éditeurs

---

## 🇫🇷 Table des matières (FR)
1. Installation et compilation
2. Usage rapide
3. Exemples
4. Librairie standard & modules
5. Développement & tests
6. CI / Releases
7. Contribution
8. Licence & contacts

---

## 1) 🇫🇷 Installation & compilation (Linux / macOS)

Le dépôt officiel du compilateur Goscript, de Golem, du script d'installation
et de leurs releases est
[`gopu-inc/goscript`](https://github.com/gopu-inc/goscript). Les instructions
complètes sont dans [`docs/golem.md`](docs/golem.md).

Prérequis (exemples pour Debian/Ubuntu) :
```bash
sudo apt-get update
sudo apt-get install -y build-essential flex bison libffi-dev zlib1g-dev libreadline-dev make gcc
```
macOS (Homebrew) :
```bash
brew install flex bison libffi make
```

Construire depuis la source :
```bash
git clone https://github.com/gopu-inc/goscript.git
cd goscript
make
# compiler: ./build/bin/gd
sudo make install PREFIX=/usr/local  # installe gd et golem
```

Pour éviter `sudo`, utilisez `make install PREFIX="$HOME/.local"` puis ajoutez
`$HOME/.local/bin` au `PATH`. L'installateur officiel `install.sh` télécharge
une release GitHub avec vérification SHA-256; si aucune archive n'est publiée
pour la plateforme, il clone ce même dépôt et compile depuis les sources.
Voir `docs/golem.md` pour les prérequis, les commandes de release et Golem.

---

## 2) 🇫🇷 Usage rapide

Exécuter un script :
```bash
./build/bin/gd exemples/hello.gjs
```

Options courantes (extrait du binaire):
```text
./build/bin/gd --version
./build/bin/gd <script.gjs> [args...]
```

Exécuter une commande shell depuis Goscript (exemples) :
```gjs
lt files = sysf("ls -la")
println(files)
if sh("mkdir -p /tmp/goscript-test") == 0 { println("OK") }
```

API asynchrone (await):
```gjs
async fn fetch() {
  lt out = await sysf("curl -s https://api.github.com")
  ret out
}

fn main() {
  lt data = await fetch()
  println(data)
}
```

---

## 3) 🇫🇷 Exemples
Le dossier `exemples/` contient une grande collection de scripts de démonstration: I/O, réseau, struct, modules, tests unitaires simples, etc.

Lancer un exemple spécifique :
```bash
./build/bin/gd exemples/test_http.gjs
```

---

## 4) 🇫🇷 Librairie standard & modules

Le répertoire `lib/` contient les modules natifs et wrappers utiles:
- `fs` : read/write, mkdir, ls, exists
- `json` : parsing/serialisation
- `http`, `httplib` : utilitaires HTTP
- `shttp` / `flout` : frameworks légers pour serveurs
- `sqlite` : wrapper sqlite basique
- `__builtin__` : fonctions de base (len, type_of, assert...)

Créer un module:
```gjs
golem math
pub fn add(a, b) { ret a + b }
```

Importer :
```gjs
import math as m
println(m::add(2,3))
```

---

## 5) 🇫🇷 Développement & tests

Rappels utiles pour contributeurs:
- Compiler: `make`
- Nettoyer: `make clean`
- Installer localement: `make install`

Tests locaux (si présents):
```bash
if [ -d tests ]; then for t in tests/*.gjs; do ./build/bin/gd "$t"; done; fi
```

Linter / validation grammar (VSCode ext):
```bash
npm install
npm run build
```

CI: voir `.github/workflows/goscript-buil.yml` — compile sur Ubuntu & macOS, exécute des vérifications simples et upload d'artifacts.

---

## 6) 🇫🇷 CI / Releases
- Le workflow [`goscript-buil.yml`](.github/workflows/goscript-buil.yml) du dépôt officiel compile et teste les plateformes prévues.
- Lors d'un tag `v*`, il prépare les archives installables de Goscript + Golem, publie leurs checksums et crée une GitHub Release sur `gopu-inc/goscript`.
- Les chemins d'installation et les prérequis sont documentés dans [`docs/golem.md`](docs/golem.md).

---

## 7) Merci ! Guide rapide :
1. Fork → créez une branche descriptive `feature/…` ou `fix/…`
2. Ouvrez une PR avec description et tests si possible
3. Respectez le style existant et ajoutez des exemples dans `exemples/`

Code de conduite: respecter les échanges civilisés (utilisez issues/PRs sur GitHub).

---

## 8) 🇫🇷 Licence & contact
Licence: MIT (voir `LICENSE` si présent).
Bugs / demandes: https://github.com/gopu-inc/goscript/issues

---


# 🇬🇧 English — Quick reference (concise)

Goscript is a compact, runtime-dynamic scripting language with strong shell integration and a small standard library. The main compiled binary is `gd`.

Build and install from the official repository (Linux/macOS):
```bash
git clone https://github.com/gopu-inc/goscript.git
cd goscript
# prerequisites: gcc, make, flex, bison, libffi and zlib development files
make
./build/bin/gd --version
sudo make install PREFIX=/usr/local
golem help
```

The official `install.sh` downloads and verifies a platform release from this
repository, or builds from a temporary clone of this repository when a
prebuilt release is unavailable. See [`docs/golem.md`](docs/golem.md).

Features summary:
- Dynamic typing, familiar syntax (`fn`, `struct`, `impl`, `match`, `async/await`)
- Native shell integration: `sysf` (captured stdout), `sh` (exit code)
- Modules in `lib/`, examples in `exemples/`
- Editor support (VSCode grammar in `grammars/`, package.json)

Development:
- Build: `make`
- Grammar validation: `npm run build` (uses Node.js's built-in JSON parser)
- CI: GitHub Actions (see `.github/workflows/goscript-buil.yml`)

Contributing & reporting bugs: open an issue or PR on GitHub.

---

## Appendices

- File structure overview
```
./src/       # C source: parser, interpreter
./lib/       # standard library in .gjs
./exemples/  # many sample scripts
./lib/golem/ # Golem package manager module
./genv/       # environment manager
./grammars/   # editor grammars
```

- Contacts: https://github.com/gopu-inc/goscript

---

 GOPU inc
README generated/updated by automation (commit includes Co-authored-by: Lentreprise C.M.O)
