#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fe.h"

static fe_Object* load_module(fe_Context *ctx, fe_Object *args, int is_local) {
  fe_Object *arg = fe_nextarg(ctx, &args);
  char path_buf[256];
  char file_path[512];
  char target_symbol[128];
  char *first_sep;
  FILE *fp;
  int gc;
  fe_Object *obj;

  target_symbol[0] = '\0';
  fe_tostring(ctx, arg, path_buf, sizeof(path_buf));

  /* 1. Extraction du chemin et du symbole cible */
  first_sep = strstr(path_buf, "::");
  if (first_sep) {
    /* On cherche le dernier segment après le dernier ':' */
    char *last_colon = strrchr(path_buf, ':');
    if (last_colon) {
      strcpy(target_symbol, last_colon + 1);
    }
    /* On coupe la chaîne au premier ':' pour avoir le nom du fichier */
    *first_sep = '\0';
  }

  /* 2. Construction du chemin du fichier */
  if (is_local) {
    sprintf(file_path, "./%s.fe", path_buf);
  } else {
    /* Chemin global par défaut */
    sprintf(file_path, "/usr/local/lib/goscript/%s.fe", path_buf);
  }

  /* 3. Ouverture et lecture du fichier */
  fp = fopen(file_path, "rb");
  if (!fp) {
    char err_msg[512];
    sprintf(err_msg, "Module not found: %s", file_path);
    fe_error(ctx, err_msg);
  }

  /* 4. Évaluation du contenu du fichier */
  gc = fe_savegc(ctx);
  while ((obj = fe_readfp(ctx, fp))) {
    fe_eval(ctx, obj);
    fe_restoregc(ctx, gc);
  }
  fclose(fp);

  /* 5. Retourne l'objet spécifique si demandé, sinon retourne 't' */
  if (target_symbol[0] != '\0') {
    fe_Object *sym = fe_symbol(ctx, target_symbol);
    return fe_eval(ctx, sym);
  }

  return fe_bool(ctx, 1);
}

/* Fonctions exportées */
fe_Object* f_use(fe_Context *ctx, fe_Object *args) {
  return load_module(ctx, args, 0);
}

fe_Object* f_nm(fe_Context *ctx, fe_Object *args) {
  return load_module(ctx, args, 1);
}
