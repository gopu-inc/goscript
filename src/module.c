#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fe.h"

static fe_Object* load_module(fe_Context *ctx, fe_Object *args, int is_local) {
  fe_Object *arg = fe_nextarg(ctx, &args);
  char path_buf[256];
  char file_path[512];
  char target_symbol[128] = "";
  char *first_sep;
  FILE *fp;
  int gc;
  fe_Object *obj;

  fe_tostring(ctx, arg, path_buf, sizeof(path_buf));

  /* Parser le format : dossier/fichier::type::nom */
  first_sep = strstr(path_buf, "::");
  if (first_sep) {
    char *rest, *last_sep, *temp;
    *first_sep = '\0'; 
    
    rest = first_sep + 2;
    last_sep = rest;
    while ((temp = strstr(last_sep, "::")) != NULL) {
      last_sep = temp + 2;
    }
    strcpy(target_symbol, last_sep);
  }

  /* Construire le chemin */
  if (is_local) {
    snprintf(file_path, sizeof(file_path), "./%s.fe", path_buf);
  } else {
    snprintf(file_path, sizeof(file_path), "/usr/local/lib/goscript/%s.fe", path_buf);
  }

  /* Ouvrir et évaluer */
  fp = fopen(file_path, "rb");
  if (!fp) {
    char err[512];
    snprintf(err, sizeof(err), "Module not found: %s", file_path);
    fe_error(ctx, err);
  }

  gc = fe_savegc(ctx);
  while ((obj = fe_readfp(ctx, fp))) {
    fe_eval(ctx, obj);
    fe_restoregc(ctx, gc);
  }
  fclose(fp);

  if (target_symbol[0] != '\0') {
    return fe_eval(ctx, fe_symbol(ctx, target_symbol));
  }

  return fe_bool(ctx, 1);
}
