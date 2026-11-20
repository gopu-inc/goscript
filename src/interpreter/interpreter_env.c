#include "interpreter.h"

/*
 * Environnements : tableau de variables + index de hachage.
 *
 * Les petits scopes (< ENV_INDEX_MIN variables) restent en recherche
 * linéaire, ce qui est le plus rapide pour quelques entrées. Au-delà
 * (typiquement le scope global, qui contient des centaines de fonctions C
 * enregistrées), un index à adressage ouvert évite un strcmp par variable
 * à chaque accès.
 */

#define ENV_INDEX_MIN 8

static unsigned int env_hash(const char* s) {
    unsigned int h = 2166136261u;            /* FNV-1a */
    while (*s) { h ^= (unsigned char)*s++; h *= 16777619u; }
    return h;
}


/*
 * Internement des noms de variables : un nom n'est alloué qu'une fois pour
 * tout le programme (l'ensemble des noms est borné par le source). Cela évite
 * un strdup par variable et par appel de fonction, et permet de libérer un
 * scope sans toucher aux noms.
 */
static char** intern_tab = NULL;
static unsigned int intern_cap = 0, intern_count = 0;

static char* intern_name(const char* name) {
    if (intern_cap == 0 || (intern_count + 1) * 2 > intern_cap) {
        unsigned int ncap = intern_cap ? intern_cap * 2 : 1024;
        char** ntab = calloc(ncap, sizeof(char*));
        for (unsigned int i = 0; i < intern_cap; i++) {
            if (!intern_tab[i]) continue;
            unsigned int pos = env_hash(intern_tab[i]) & (ncap - 1);
            while (ntab[pos]) pos = (pos + 1) & (ncap - 1);
            ntab[pos] = intern_tab[i];
        }
        free(intern_tab);
        intern_tab = ntab;
        intern_cap = ncap;
    }
    unsigned int mask = intern_cap - 1;
    unsigned int pos = env_hash(name) & mask;
    while (intern_tab[pos]) {
        if (strcmp(intern_tab[pos], name) == 0) return intern_tab[pos];
        pos = (pos + 1) & mask;
    }
    intern_tab[pos] = strdup(name);
    intern_count++;
    return intern_tab[pos];
}

Environment* create_env(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    env->parent = parent;
    env->vars = NULL;
    env->var_count = 0;
    env->var_capacity = 0;
    env->index = NULL;
    env->index_cap = 0;
    return env;
}

static void env_index_insert(Environment* env, int var_idx) {
    unsigned int mask = (unsigned int)env->index_cap - 1;
    unsigned int pos = env_hash(env->vars[var_idx].name) & mask;
    while (env->index[pos] != -1) pos = (pos + 1) & mask;
    env->index[pos] = var_idx;
}

static void env_index_rebuild(Environment* env, int cap) {
    free(env->index);
    env->index_cap = cap;
    env->index = malloc(sizeof(int) * (size_t)cap);
    for (int i = 0; i < cap; i++) env->index[i] = -1;
    for (int i = 0; i < env->var_count; i++) env_index_insert(env, i);
}

/* Cherche une variable dans CE scope uniquement. Renvoie son indice ou -1. */
static int env_find_local(Environment* env, const char* name) {
    if (env->index_cap) {
        unsigned int mask = (unsigned int)env->index_cap - 1;
        unsigned int pos = env_hash(name) & mask;
        while (env->index[pos] != -1) {
            int i = env->index[pos];
            if (strcmp(env->vars[i].name, name) == 0) return i;
            pos = (pos + 1) & mask;
        }
        return -1;
    }
    for (int i = 0; i < env->var_count; i++) {
        if (env->vars[i].name && strcmp(env->vars[i].name, name) == 0) return i;
    }
    return -1;
}

void env_set(Environment* env, char* name, Value value) {
    if (!env) return;

    /* 1. Variable existante ? (on remonte les parents) -> mise à jour */
    for (Environment* curr = env; curr; curr = curr->parent) {
        int i = env_find_local(curr, name);
        if (i >= 0) {
            curr->vars[i].value = value;
            return;
        }
    }

    /* 2. Sinon, création dans l'environnement COURANT */
    if (env->var_count >= env->var_capacity) {
        env->var_capacity = env->var_capacity == 0 ? 10 : env->var_capacity * 2;
        env->vars = realloc(env->vars, env->var_capacity * sizeof(*env->vars));
    }

    env->vars[env->var_count].name = intern_name(name);
    env->vars[env->var_count].value = value;
    env->var_count++;

    /* Index : création au seuil, agrandissement si charge > 50 % */
    if (env->index_cap == 0) {
        if (env->var_count >= ENV_INDEX_MIN) env_index_rebuild(env, 32);
    } else if (env->var_count * 2 > env->index_cap) {
        env_index_rebuild(env, env->index_cap * 2);
    } else {
        env_index_insert(env, env->var_count - 1);
    }
}

Value* env_get(Environment* env, char* name) {
    for (; env; env = env->parent) {
        int i = env_find_local(env, name);
        if (i >= 0) return &env->vars[i].value;
    }
    return NULL;
}

/* Libère un scope créé par create_env (les noms sont internés : non libérés).
 * Les valeurs ne sont pas libérées, comme avec le simple free() d'avant. */
void env_free(Environment* env) {
    if (!env) return;
    free(env->vars);
    free(env->index);
    free(env);
}
