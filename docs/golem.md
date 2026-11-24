# Golem, gestionnaire de paquets Goscript

Golem est le gestionnaire de paquets de Goscript. Le lanceur `golem` et le
paquet `lib/golem/__self__.gjs` sont écrits en Goscript. `gd` exécute le
lanceur; les primitives système de bas niveau sont fournies par l'interpréteur.
Le dépôt canonique du compilateur, de Golem, de l'installateur et de la CI est
[`gopu-inc/goscript`](https://github.com/gopu-inc/goscript). Les releases et le
workflow cités ci-dessous viennent de ce dépôt; le serveur du registre ne
construit ni ne distribue ces exécutables.

## Construire et installer Goscript + Golem

### Depuis les sources officielles

Prérequis Linux (Debian/Ubuntu):

```sh
sudo apt-get update
sudo apt-get install -y build-essential flex bison libffi-dev zlib1g-dev make
```

Sur macOS, installez Xcode Command Line Tools et Homebrew, puis:

```sh
brew install flex bison libffi make
```

Clonez le dépôt officiel, compilez `gd`, puis installez aussi le lanceur Golem
et ses fichiers Goscript:

```sh
git clone https://github.com/gopu-inc/goscript.git
cd goscript
make
./build/bin/gd --version
sudo make install PREFIX=/usr/local
golem help
```

`make` construit `build/bin/gd` ainsi que les alias `gbc` et `gld`.
`make install` copie le compilateur et les alias dans `PREFIX/bin`, puis
installe le lanceur `golem` et son code requis dans `PREFIX/share/goscript`.
Pour une installation sans privilèges, utilisez un préfixe utilisateur et
ajoutez son dossier `bin` au `PATH`:

```sh
make install PREFIX="$HOME/.local"
export PATH="$HOME/.local/bin:$PATH"
golem help
```

### Installateur et releases GitHub

`install.sh` et `update.sh` sont maintenus dans le même dépôt officiel.
L'installateur choisit le paquet précompilé pour Linux/macOS (hors Termux),
le télécharge depuis les GitHub Releases de `gopu-inc/goscript`, vérifie son
SHA-256, puis installe à `/usr/local` par défaut. Choisissez un autre
emplacement avec `PREFIX`:

```sh
curl -fsSLO https://raw.githubusercontent.com/gopu-inc/goscript/refs/heads/main/install.sh
less install.sh  # inspecter le script avant de l'exécuter
sudo sh install.sh

# Ou, sans sudo:
PREFIX="$HOME/.local" sh install.sh
```

Le script de mise à jour et les scripts PowerShell sont également disponibles
directement depuis le dépôt officiel :

```sh
curl -fsSL https://raw.githubusercontent.com/gopu-inc/goscript/refs/heads/main/update.sh | sh
```

```powershell
Invoke-WebRequest https://raw.githubusercontent.com/gopu-inc/goscript/refs/heads/main/install.ps1 -OutFile install.ps1
.\install.ps1
Invoke-WebRequest https://raw.githubusercontent.com/gopu-inc/goscript/refs/heads/main/update.ps1 -OutFile update.ps1
.\update.ps1
```

Sur les plateformes sans archive précompilée, l'installateur installe les
outils de compilation disponibles, clone
`https://github.com/gopu-inc/goscript.git` dans un répertoire temporaire,
compile `gd` et exécute `make install`. Pour une version précise, définissez
`GOSCRIPT_VERSION` sur le tag de release (par exemple `v1.0.0`). `update.sh`
met à jour une installation existante via cet installateur; il ne change pas
la source du projet.

Sur Termux/Android, aucune archive GNU/Linux n'est utilisée : l'installateur
installe les outils requis avec `pkg`, compile avec Clang pour Bionic et fixe
l'alignement TLS ARM64 requis par son chargeur. Après avoir installé cette
version de Golem, le runtime peut aussi être installé ou mis à jour avec :

```sh
golem install goscript
golem install goscript v1.0.0
```

Cette forme réservée appelle l'installateur officiel en réutilisant le préfixe
de l'installation courante; les autres noms restent des paquets du registre.

Sur Windows, téléchargez l'archive `goscript-windows-x86_64.zip` de la GitHub
Release, extrayez-la dans un dossier permanent et ajoutez son sous-dossier
`bin` au `PATH`. Elle contient `gd.exe`, `golem.cmd` et les fichiers partagés
nécessaires; `install.sh` est un script POSIX, pas un installateur PowerShell.

Les archives de release ne sont créées que par le workflow
[`goscript-buil.yml`](https://github.com/gopu-inc/goscript/blob/main/.github/workflows/goscript-buil.yml)
sur `gopu-inc/goscript`: il compile les plateformes prévues, installe dans un
préfixe de staging, empaquette `bin/` et `share/`, génère les checksums, puis
publie les fichiers sur GitHub lors d'un tag `v*`. Une compilation depuis les
sources ne dépend pas de l'existence d'une release.

## Installation locale d’un exécutable

Pour installer le paquet du répertoire courant, ses dépendances et une
commande exécutable à partir du manifeste :

```sh
sudo golem install --local .
```

Dans `[metadata]`, `entry` choisit le fichier Goscript lancé par `gd -c`, et
`command` nomme le script créé dans `/usr/local/bin` :

```toml
[metadata]
name = "curse"
entry = "main.gjs"
command = "curse"
```

Golem installe le paquet et les dépendances résolues dans
`/usr/local/share/goscript`, puis crée `/usr/local/bin/curse`. Le lanceur
exécute `gd -c curse` et transmet les arguments au programme. Pour une
installation sans privilèges, définir `GOSCRIPT_MODULE_DIR` et
`GOSCRIPT_BIN_DIR` vers des dossiers accessibles en écriture et ajouter le
second au `PATH`.

Les commandes `golem install <nom>` et `golem install` gardent leur rôle de
résolution du registre ou des dépendances du projet dans `modules/`.
Pour remplacer directement un paquet déjà installé par sa version courante du
registre, utiliser `golem upgrade <nom>`; Golem télécharge et vérifie l’archive,
installe le paquet puis résout ses dépendances.

## Installation et bibliothèque standard

`make standard-packages` construit toutes les archives `.tar.bool` standard
ainsi que le méta-package `base`. Une fois ces paquets publiés, un projet peut
installer les bibliothèques standard avec :

```sh
golem install base
```

Pour publier l'ensemble dans le registre après `golem login`, lancer
`make publish-standard-packages`. La cible publie d'abord les modules standards
et `base` en dernier, car `base` dépend des versions standard listées dans son
manifeste.

Avant de construire un paquet qui déclare des dépendances, Golem vérifie les
modules installés dans `modules/` et les copie récursivement dans `vendor/`.
L’archive contient ces copies; le chargeur Goscript cherche ensuite les imports
dans le `vendor/` du paquet. Le paquet construit peut donc être déplacé ou lancé
après suppression des dépendances installées séparément.

`make install` installe `gd`, le lanceur Golem, le builtin Goscript et le code
interne du gestionnaire sous `share/goscript`. Il ne crée pas de répertoires
globaux `lib/` ou `modules/`; Golem installe les paquets standard dans le
`modules/` du projet courant, sauf `golem install --local .` qui installe
explicitement le paquet et sa commande dans le préfixe partagé.

`install.sh` télécharge uniquement l'archive binaire de la release GitHub qui
correspond au système, vérifie son SHA-256 et installe ces commandes. Il ne
clone ni ne télécharge le dépôt source. `update.sh` utilise l'installateur servi
par GitHub Raw. Les routes historiques du registre redirigent également vers
les scripts du dépôt officiel.

## Commandes

```sh
./golem help
./golem init mon-paquet
./golem search http
./golem info http
./golem install http
./golem install
./golem build
./golem login mon-compte
./golem publish
./golem logout
./golem list
./golem remove http
./golem update
./golem doctor
```

`./golem install` sans nom installe les dépendances du manifeste courant.
`./golem install nom [version]` installe un paquet du registre. Les dépendances
des paquets sont chargées depuis leur Manifest.toml, avec une profondeur
maximale de 12.

`golem search` accepte plusieurs mots et `golem info <nom> [version] [scope]`
affiche les métadonnées et les versions publiées. Avant l'envoi, `golem publish`
vérifie la disponibilité du registre, le propriétaire du nom et l'existence de
la version. Seul le propriétaire peut publier de nouvelles versions; une version
existante est immuable. Une republication identique est traitée comme une
opération sans changement. `golem logout` supprime le jeton et le compte local.

## Manifeste

```toml
[metadata]
name = "mon-paquet"
version = "0.1.0"
release = "r0"
arch = "x86_64"
description = "Module Goscript"
author = "Auteur"
license = "MIT"
main = "__self__.gjs"
files = ["__self__.gjs", "main.gjs"]
scope = "public"

[dependencies]
httplib = ">=1.1.0"
```

Le générateur de projet `golem init` crée Manifest.toml ainsi que les fichiers
Goscript initiaux. `golem build` suit la liste metadata.files si elle existe;
sinon il inclut les fichiers Goscript à la racine, README.md et LICENSE. Les
archives gzip utilisent le suffixe `.tar.bool` attendu par le registre.

La première ligne de `__self__.gjs` identifie le paquet avec la déclaration
`golem mon-paquet`. Quand un dossier de paquet est importé, `__self__.gjs` est
chargé comme point d'entrée : ses exports deviennent accessibles depuis le
paquet importé et ses instructions de niveau supérieur s'exécutent une fois.

Les téléchargements vérifient le SHA-256 annoncé par le registre et inspectent
les chemins de l'archive avant extraction. Les fichiers sont installés dans
modules/. Golem prépare la nouvelle version dans un dossier temporaire puis
remplace le paquet installé en conservant une sauvegarde en cas d'échec.

`golem login` demande le mot de passe sans l'afficher. Le jeton et le nom du
compte sont conservés dans `~/.config/golem/` avec des permissions limitées à
l'utilisateur.
`golem publish` publie l'archive du projet selon metadata.scope, qui vaut
`public` par défaut.

Le lanceur `golem` utilise `#!/bin/env gd`. Il est installé dans
`/usr/local/bin` par `make install`, avec l'installateur et les modules
Goscript requis dans `share/goscript`. L'ancien point d'entrée `gpm.gjs` reste
un alias de compatibilité.
