# Cache de compilation Goscript

À chaque lancement d’un fichier `.gjs`, Goscript crée ou réutilise à côté du
fichier un cache dans `__gocache__/`. Par exemple, `server.gjs` produit
`__gocache__/server.goscript.gbc`. Les modules importés utilisent le même
cache dans leur propre répertoire.

Le cache contient le flux lexical sérialisé pour éviter de relancer le lexer.
Goscript vérifie l’empreinte et la taille du source ainsi que la version du
format à chaque lancement. Une modification du source ou du format provoque sa
recréation. Le cache est une optimisation facultative : si le répertoire ne
peut pas être écrit ou si le cache est invalide, Goscript relit le source.

Le runtime possède également un stack VM sélectionnable avec `gd --vm`. Il
compile et exécute les littéraux, variables scalaires, opérateurs usuels,
affectations, `if`, `while`, les boucles `for` et `for-in-range`, `return`,
les opérateurs logiques avec court-circuit, `print` et `println`. Il refuse les
imports, les appels Goscript généraux, tableaux, dictionnaires, closures, objets
et async. Ces constructions restent disponibles en lançant le programme sans
`--vm`; `--vm` affiche une erreur de compilation au lieu de les ignorer.

Le stack VM vérifie également les indices de constantes, les slots locaux et
les destinations de saut avant de les utiliser. Les opcodes non implémentés
échouent explicitement au lieu d’avancer silencieusement dans le bytecode.

On peut lancer directement le cache avec `gd __gocache__/server.goscript.gbc`.
Le chargeur reconnaît son en-tête `GJSCACHE`, restaure les tokens et déduit le
chemin d’origine du script pour résoudre ses imports. Le cache reste utilisable
si le fichier `.gjs` source est supprimé.

Malgré son suffixe `.gbc`, ce fichier est un cache de tokens, pas le bytecode
exécutable du stack VM. Le parseur s’exécute encore à chaque lancement. Les
conteneurs GBC1 émis par `gd --emit-gbc` sont un format distinct. La sérialisation
portable du bytecode VM reste à implémenter.

`make install` ajoute les signatures de ces deux formats à `/etc/magic` sans
remplacer les règles locales déjà présentes. Après installation, la commande
`file` identifie les caches `GJSCACHE` et les conteneurs `GBC1`.
