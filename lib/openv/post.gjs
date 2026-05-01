/*
OPENV - v0.1.0
 par gopu copyright (c) 2026 GPM LICENCE

C'EST ( software ) ET OPEN SOURCE POUR LE
LANGAGE GOSCRIPT * POUR USAGE PUBLIC

C'EST UN FRAMEWORK OPENV SOURCE FREE POUR
USAGE SUIVANT:
   COMMERCIALE: 5
   PRODUCTION: 4
   DIVERTISSEMENT: 1
   DEVELOPEMENT: 3
   AGREEFIN: 2
ALORS TENER A BIEN VERIFIER LE NOTICE D'USAGE 
DANS LE FICHIER  ( NOT.sm )
   VOILA LE POURQUOI SERT OPENV - v0.1.0
*/



module post
import ui
import fs

/*
ce module sert juste a inserer de variable plus 
facilement grace a export et sys

comme ça on peut interargir avec l'os direct

*/

fn Env(name, env) {
   // assertation pour gestion d'erreur
   if name == "" || env == "" {
      println(ui::yellow("non env set"))
   }
   
   if fs::read(".openv") == name || fs::read(".openv") == env {
       ret "your env all existing change name or env"
   } 
   lt result = fs::append(".openv", f"{name}={env}")
   ret result
}
