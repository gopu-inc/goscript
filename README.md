


---

# 📘 Documentation Officielle de Goscript

[![Goscript](https://img.shields.io/badge/language-Goscript-7c3aed.svg)](https://github.com/gopu-inc/goscript)

**Goscript** est un langage de script moderne, typé dynamiquement au moment de l'exécution, conçu pour être rapide, expressif, et particulièrement puissant pour l'interaction système et l'exécution de commandes shell.

---

## 📑 Table des matières
1. [Syntaxe de Base](#1-syntaxe-de-base)
2. [Variables et Constantes](#2-variables-et-constantes)
3. [Types de Données](#3-types-de-données)
4. [Opérateurs](#4-opérateurs)
5. [Structures de Contrôle](#5-structures-de-contrôle)
6. [Fonctions et Lambdas](#6-fonctions-et-lambdas)
7. [Programmation Orientée Objet (Structs & Impl)](#7-programmation-orientée-objet)
8. [Intégration Système (Shell & FFI)](#8-intégration-système-shell--ffi)
9. [Programmation Asynchrone](#9-programmation-asynchrone)
10. [Gestion des Erreurs](#10-gestion-des-erreurs)
11. [Modules et Importations](#11-modules-et-importations)
12. [Librairie Standard](#12-librairie-standard)

---

## 1. Syntaxe de Base

Le point d'entrée d'un programme Goscript est la fonction `main`. L'affichage se fait souvent via `println` ou `print`.

```rust
// Ceci est un commentaire sur une ligne
/* Ceci est un 
   commentaire multi-lignes */

fn main() {
    println("Hello, Goscript!")
    ret 0
}
```
*Note : Le mot-clé de retour est `ret` (et non return).*

---

## 2. Variables et Constantes

Goscript propose trois façons de déclarer des variables, favorisant l'immuabilité par défaut.

| Mot-clé | Description |
|:---|:---|
| `lt` | Déclare une variable standard (équivalent de *let*). |
| `muts` | Déclare une variable **mutable** (modifiable). |
| `cn` | Déclare une **constante** (évaluée à l'exécution). |

```rust
fn main() {
    lt name = "Alice"     // Variable simple
    cn PI = 3.14159       // Constante

    muts counter = 0      // Variable mutable
    counter += 1          // Modification permise
    
    ret 0
}
```

---

## 3. Types de Données

Bien que le typage soit dynamique, Goscript reconnaît les types internes suivants : `int`, `float`, `string`, `bool`, `nil`, tableaux (`array`) et dictionnaires (`dict`).

### Chaînes de caractères et F-Strings
```rust
lt s1 = "Texte normal"
lt s2 = 'Texte simple'
lt multi = """Texte sur
plusieurs lignes"""

// F-strings (Interpolation)
lt age = 30
lt msg = f"J'ai {age} ans." // J'ai 30 ans.
```

### Tableaux (Arrays)
```rust
muts arr = [10, 20, 30]
println(arr[0])  // Affiche 10
arr[1] = 99      // Modification
```

### Dictionnaires (Dicts)
```rust
lt d = dict {
    "nom" => "Goscript",
    "version" => 2.0
}
println(d["nom"]) // Affiche Goscript
```

---

## 4. Opérateurs

Goscript supporte un large éventail d'opérateurs :

*   **Arithmétiques :** `+`, `-`, `*`, `/`, `%`
*   **Assignation :** `=`, `+=`, `-=`, `*=`, `/=`, `%=`
*   **Comparaison :** `==`, `!=`, `<`, `>`, `<=`, `>=`
*   **Logiques :** `&&` (ET), `||` (OU), `!` (NON)
*   **Spéciaux :**
    *   `..` et `..=` : Création de plages (ranges).
    *   `|>` : Opérateur de pipe (ex: `val |> func`).

---

## 5. Structures de Contrôle

### Conditions (`if / else if / else`)
```rust
if score >= 90 {
    println("A")
} else if score >= 80 {
    println("B")
} else {
    println("C")
}
```

### Pattern Matching (`match`)
Très puissant, le `match` remplace avantageusement le `switch`. Le mot clé par défaut est `_`.
```rust
match value {
    1 => println("Un")
    2 => ret "Deux"
    _ => println("Autre")
}
```

### Boucles (`while`, `loop`, `for`)
```rust
// While
muts i = 0
while i < 5 { i += 1 }

// Loop (boucle infinie avec condition de sortie)
loop {
    if condition { break }
}

// For classique
for i = 0; i < 10; i += 1 { ... }

// For-In (Itération sur tableau ou range)
for x in [1, 2, 3] { println(x) }
for i in 0..10 { println(i) }     // Exclusif (0 à 9)
for i in 0..=10 { println(i) }    // Inclusif (0 à 10)
```

---

## 6. Fonctions et Lambdas

Les fonctions sont déclarées avec `fn`. Elles peuvent être publiques (`pub fn`) pour être exportées d'un module.

```rust
// Typage optionnel des arguments et du retour
pub fn add(a: int, b: int): int {
    ret a + b
}

// Syntaxe courte (Arrow function)
fn multiply(a, b) -> a * b
```

### Lambdas (Fonctions Anonymes)
```rust
muts double = lambda x { ret x * 2 }
println(double(5)) // 10

// Les lambdas supportent les closures
muts multiplier = lambda factor {
    lambda x { ret x * factor }
}
```

---

## 7. Programmation Orientée Objet

Goscript utilise une composition basée sur les `struct` et les `impl` (comme en Rust).

```rust
// Déclaration
struct Person {
    name: string,
    age: int
}

// Héritage possible
struct Employee extends Person {
    job: string
}

// Implémentation des méthodes
impl Person {
    fn greet(self) {
        println("Bonjour, " + self.name)
    }
}

fn main() {
    // Instanciation avec le mot-clé `new`
    lt alice = new Person {
        name: "Alice",
        age: 30
    }
    alice.greet()
}
```

---

## 8. Intégration Système (Shell & FFI)

C'est la fonctionnalité phare de Goscript. Il exécute nativement des commandes shell de deux manières :

### `sysf` et `sh`
*   `sysf("cmd")` : Exécute la commande et **retourne la sortie standard (stdout)** sous forme de chaîne de caractères (`string`).
*   `sh("cmd")` : Exécute la commande et **retourne le code de retour** (`int`).

```rust
// Capture le résultat
lt files = sysf("ls -la")
println(files)

// Vérifie si une commande a réussi
if sh("mkdir /tmp/test") == 0 {
    println("Dossier créé")
}

// Syntaxe sans parenthèses possible
lt date = sysf "date '+%Y-%m-%d'"
```

### Blocs non-sûrs (`unsafe`)
Certaines opérations mémoire nécessitent un bloc `unsafe` :
```rust
unsafe {
    // Opérations FFI bas niveau
}
```

---

## 9. Programmation Asynchrone

Goscript gère l'asynchrone de manière native (promesses sous-jacentes) avec `async` et `await`. Idéal pour les appels réseau via le shell.

```rust
async fn fetch_data() {
    lt cmd = "curl -s 'https://api.github.com'"
    lt result = await cmd
    ret result
}

fn main() {
    lt data = await fetch_data()
    println(data)
}
```
*Il existe aussi le mot clé `spawn` pour lancer des processus en parallèle.*

---

## 10. Gestion des Erreurs

### Try / Catch / Finally / Throw
```rust
fn divide(a, b) {
    if b == 0 {
        throw "Division par zéro!"
    }
    ret a / b
}

try {
    divide(10, 0)
} catch (e) {
    println("Erreur interceptée: " + e)
} finally {
    println("Exécution terminée.")
}
```

### Sauts non locaux (NNL / JMP)
Pour un contrôle de flux avancé :
```rust
nnl my_label {
    println("Avant le saut")
    jmp my_label 42 // Saute en dehors du bloc et retourne 42
    println("Jamais exécuté")
}
```

---

## 11. Modules et Importations

Goscript possède un système de modules robuste.

### Déclaration d'un module
Fichier `math.gjs` :
```rust
module math

pub cn PI = 3.1415
pub fn add(a, b) { ret a + b }
```

### Importation
```rust
// Import simple
import fs

// Import avec alias
import math as m

// Import avec contraintes (seulement certaines fonctions)
import io { only: [read, write] }

fn main() {
    println(m::PI)
    fs::mkdir("/tmp/test")
}
```

---

## 12. Librairie Standard

Goscript intègre plusieurs modules natifs et wrappers C dans sa librairie standard (`lib/*.gjs`).

*   **`__builtin__`** : Inclus automatiquement (`assert`, `str`, `ints`, `abs`, `max`, `len`, `type_of`).
*   **`fs`** : Système de fichiers (`read`, `write`, `rm`, `cp`, `mv`, `mkdir`, `ls`, `exists`).
*   **`sys` / `__os`** : Variables d'environnement, infos OS, process (`env`, `pwd`, `hostname`, `pid`).
*   **`json`** : Parsing JSON léger (`get`, `value`, `has_key`, `type_of`).
*   **`http`** : Requêtes web (`Get`, `Post`, `GetWithTimeout`).
*   **Wrappers IA (`deepseek`, `groq`)** :
    ```rust
    import deepseek
    lt key = "sk-..."
    println(deepseek::ask(key, "Bonjour !"))
    ```
*   **`ui`** : Interfaces terminal avec support complet des couleurs ANSI (`success`, `error`, `progress_bar_color`, `spinner_start`).

---
*copyright © Goscript (2026).*
