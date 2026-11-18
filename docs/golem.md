# Golem, gestionnaire de paquets Goscript

Golem est le gestionnaire de paquets de Goscript. Le lanceur `golem` et le
paquet `lib/golem/__self__.gjs` sont écrits en Goscript. `gd` exécute le
lanceur; les primitives système de bas niveau sont fournies par l'interpréteur.

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
./golem list
./golem remove http
./golem update
./golem doctor
```

`./golem install` sans nom installe les dépendances du manifeste courant.
`./golem install nom [version]` installe un paquet du registre. Les dépendances
des paquets sont chargées depuis leur Manifest.toml, avec une profondeur
maximale de 12.

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

`golem login` demande le mot de passe sans l'afficher. Le jeton est conservé
dans `~/.config/golem/token` avec des permissions limitées à l'utilisateur.
`golem publish` publie l'archive du projet selon metadata.scope, qui vaut
`public` par défaut.

Le lanceur `golem` utilise `#!/bin/env gd`. Il est installé dans
`/usr/local/bin` par `make install`, avec les modules Goscript du répertoire
lib/. L'ancien point d'entrée `gpm.gjs` reste un alias de compatibilité.
