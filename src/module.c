#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gsc.h"

static gs_Object* load_module(gs_Context *ctx, gs_Object *args, int is_local) {
  gs_Object *arg = gs_nextarg(ctx, &args);
  char path_buf[256];
  char file_path[512];
  char target_symbol[128];
  char *first_sep;
  FILE *fp;
  int gc;
  gs_Object *obj;
  gs_Object *result = gs_bool(ctx, 1); /* 't' par défaut */

  target_symbol[0] = '\0';
  gs_tostring(ctx, arg, path_buf, sizeof(path_buf));

  /* 1. Extraction du chemin et du symbole :: */
  first_sep = strstr(path_buf, "::");
  if (first_sep) {
    char *last_colon = strrchr(path_buf, ':');
    if (last_colon) {
      strcpy(target_symbol, last_colon + 1);
    }
    *first_sep = '\0';
  }

  /* 2. Construction du chemin */
  if (is_local) {
    sprintf(file_path, "./%s.gjs", path_buf);
  } else {
    sprintf(file_path, "/usr/local/lib/goscript/%s.gjs", path_buf);
  }

  /* 3. Ouverture */
  fp = fopen(file_path, "rb");
  if (!fp) {
    char err_msg[512];
    sprintf(err_msg, "Module not found: %s", file_path);
    gs_error(ctx, err_msg);
  }

  /* 4. Évaluation sécurisée */
  gc = gs_savegc(ctx);
  while ((obj = gs_readfp(ctx, fp))) {
    gs_eval(ctx, obj);
    gs_restoregc(ctx, gc);
  }
  fclose(fp);

  /* 5. Retour de l'objet ou de 't' */
  if (target_symbol[0] != '\0') {
    /* On cherche le symbole dans l'environnement global */
    result = gs_eval(ctx, gs_symbol(ctx, target_symbol));
  }

  return result;
}

gs_Object* f_use(gs_Context *ctx, gs_Object *args) {
  return load_module(ctx, args, 0);
}

gs_Object* f_nm(gs_Context *ctx, gs_Object *args) {
  return load_module(ctx, args, 1);
}
