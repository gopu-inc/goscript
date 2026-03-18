#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static fe_Object* load_module(fe_Context *ctx, fe_Object *args, int is_local) {
  /* Récupérer le premier argument (symbole ou string) */
  fe_Object *arg = fe_nextarg(ctx, &args);
  char path_buf[256];
  fe_tostring(ctx, arg, path_buf, sizeof(path_buf));

  char file_path[512];
  char target_symbol[128] = "";

  /* Parser le format : dossier/fichier::type::nom */
  char *first_sep = strstr(path_buf, "::");
  if (first_sep) {
    *first_sep = '\0'; /* path_buf contient maintenant uniquement le chemin */
    
    /* Trouver la dernière partie pour extraire le nom de la fonction/objet */
    char *rest = first_sep + 2;
    char *last_sep = rest;
    char *temp;
    while ((temp = strstr(last_sep, "::")) != NULL) {
      last_sep = temp + 2;
    }
    strcpy(target_symbol, last_sep);
  } else {
    /* Pas de '::', on charge juste le fichier */
    strcpy(file_path, path_buf);
  }

  /* Construire le chemin absolu ou relatif avec l'extension .fe */
  if (is_local) {
    snprintf(file_path, sizeof(file_path), "./%s.fe", path_buf);
  } else {
    /* TODO: Tu peux changer ce chemin pour pointer vers ta bibliothèque standard */
    snprintf(file_path, sizeof(file_path), "/usr/local/lib/ton_langage/%s.fe", path_buf);
  }

  /* Ouvrir et évaluer le fichier */
  FILE *fp = fopen(file_path, "rb");
  if (!fp) {
    char err[512];
    snprintf(err, sizeof(err), "Module not found: %s", file_path);
    fe_error(ctx, err);
  }

  int gc = fe_savegc(ctx);
  fe_Object *obj;
  while ((obj = fe_readfp(ctx, fp))) {
    fe_eval(ctx, obj);
    fe_restoregc(ctx, gc);
  }
  fclose(fp);

  /* Si on a demandé un objet spécifique (ex: 'str'), on le cherche et on le retourne */
  if (target_symbol[0] != '\0') {
    fe_Object *sym = fe_symbol(ctx, target_symbol);
    return fe_eval(ctx, sym); /* Retourne la valeur liée à ce symbole */
  }

  return fe_bool(ctx, 1); /* Retourne 't' (vrai) si tout s'est bien passé mais sans cible précise */
}

/* Enveloppes pour les fonctions natives Lisp */
fe_Object* f_use(fe_Context *ctx, fe_Object *args) {
  return load_module(ctx, args, 0); /* Global */
}

fe_Object* f_nm(fe_Context *ctx, fe_Object *args) {
  return load_module(ctx, args, 1); /* Local */
}
