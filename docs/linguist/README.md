# Faire reconnaître Goscript par GitHub

La barre « Languages » de GitHub est calculée par **github-linguist/linguist**.
Elle ne connaît que les langages présents dans sa base : le `.gitattributes`
du dépôt ne peut pas en créer un nouveau. `linguist-language=Goscript` est
donc ignoré tant que Goscript n'est pas dans Linguist.

## Ce qui est déjà fait dans ce dépôt
- `.gitattributes` : `*.gjs`/`*.gos` déclarés `linguist-language=Goscript`
  et `linguist-detectable` (actifs dès l'acceptation upstream) ; code généré
  et scripts d'outillage exclus des statistiques.
- Grammaire TextMate : `syntaxes/goscript.tmLanguage.json`
  (`scopeName: source.goscript`).
- Parseurs Bison générés en Java et en C++ supprimés : c'étaient eux qui
  faisaient apparaître « Java » et « C++ » dans la barre.

## Ce qu'il reste à faire pour l'ajout upstream
1. **Licence** : ajouter un fichier `LICENSE` (Linguist exige une licence
   libre pour la grammaire).
2. **Usage** : Linguist demande qu'une extension soit utilisée dans un
   nombre important de dépôts GitHub publics (de l'ordre de 200) avant
   d'accepter un nouveau langage. Vérifier le critère à jour dans
   `CONTRIBUTING.md` de Linguist.
3. **Conflit `.gjs`** : Linguist attribue déjà `.gjs` à *Glimmer JS*. Il
   faut soit mettre `.gos` comme extension principale, soit proposer une
   règle dans `lib/linguist/heuristics.yml` (par ex. présence de `fn main()`,
   `lt ` ou `muts ` pour Goscript, de `<template>` pour Glimmer).
4. **Exemples** : ajouter quelques vrais programmes dans
   `samples/Goscript/` de Linguist (sources du dépôt `exemples/`).
5. **Grammaire** : référencer ce dépôt dans `vendor/README.md` et lancer
   `script/add-grammar https://github.com/gopu-inc/goscript`.
6. Ajouter l'entrée de `languages-entry.yml` à `languages.yml`, puis ouvrir la PR.

## En attendant
Les fichiers `.gjs` ne sont pas comptés dans la barre (c'est voulu : les
étiqueter « Glimmer JS » serait faux). Pour afficher un langage existant à
la place, remplacer `Goscript` par son nom dans `.gitattributes`
(à éviter : c'est trompeur pour les visiteurs).
