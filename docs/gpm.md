# Compatibilité avec GPM

GPM est remplacé par Golem, le gestionnaire de paquets Goscript écrit en
Goscript. Consulte [la documentation de Golem](golem.md) pour les commandes,
le format Manifest.toml et le fonctionnement du lanceur.

L'ancien point d'entrée `gpm.gjs` est conservé comme alias vers Golem. Les
fonctions natives internes gardent temporairement le préfixe `gpm_` afin de
préserver la compatibilité avec l'interpréteur Goscript.
