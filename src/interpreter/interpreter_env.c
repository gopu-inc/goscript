#include "interpreter.h"

Environment* create_env(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    env->parent = parent;
    env->vars = NULL;
    env->var_count = 0;
    env->var_capacity = 0;
    return env;
}


void env_set(Environment* env, char* name, Value value) {
    if (!env) return;
    
    // 1. Chercher d'abord si la variable existe (en remontant les parents)
    Environment* curr = env;
    while (curr) {
        for (int i = 0; i < curr->var_count; i++) {
            if (curr->vars[i].name && strcmp(curr->vars[i].name, name) == 0) {
                curr->vars[i].value = value; // Met à jour la variable existante !
                return;
            }
        }
        curr = curr->parent;
    }
    
    // 2. Si elle n'existe nulle part, on la crée dans l'environnement COURANT
    if (env->var_count >= env->var_capacity) {
        env->var_capacity = env->var_capacity == 0 ? 10 : env->var_capacity * 2;
        env->vars = realloc(env->vars, env->var_capacity * sizeof(*env->vars));
    }
    
    env->vars[env->var_count].name = strdup(name);
    env->vars[env->var_count].value = value;
    env->var_count++;
}


Value* env_get(Environment* env, char* name) {
    if (!env) return NULL;  // Protection anti-crash
    
    for (int i = 0; i < env->var_count; i++) {
        if (env->vars[i].name && strcmp(env->vars[i].name, name) == 0) {
            return &env->vars[i].value;
        }
    }
    
    if (env->parent) {
        return env_get(env->parent, name);
    }
    return NULL;
}
