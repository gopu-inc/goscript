/*
module
get::env() par gopu inc (c) copyright 2026

Maintainer: Mauricio-100
e-mail: ceoseshell@gmail.com
version: OPENV - v0.1.0
description: a module parse all env from OPENV
             by gopu
dependances: [
          config: 2.1.0,
          ui: 1.0.0,
          fs: 2.2.0
]


*/

module get
import config
/*
c'est le module de parsage de variable avec le
signe '=' 
*/

fn env(name, path) {
   /*
   parser avec config pour obtenir le
   variable '=' variable
   */ 
   lt cmd = config::parser_conf(path, name)
   /*
   on retourne la structure de parsage
   cmd.parse
   config::parser_conf(path, env).parse
   voila comment il marche
   */
   ret cmd.parse

}
