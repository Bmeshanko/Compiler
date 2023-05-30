#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct Env *new_env() {
    struct Env *ret = (struct Env *)malloc(sizeof(struct Env));

    ret -> lines = 0;

    return ret;
}

struct Prim *new_prim(char *op, struct Tree *left, struct Tree *right) {
    struct Prim *ret = (struct Prim *)malloc(sizeof(struct Prim));

    ret -> op = strdup(op);
    ret -> left = left;
    ret -> right = right;
    ret -> type = 1;

    return ret;
}

struct Lit *new_lit(int val) {
    struct Lit *ret = (struct Lit *)malloc(sizeof(struct Lit));

    ret -> val = val;
    ret -> type = 2;

    return ret;
}

struct Let *new_let(char* id, struct Prim *val) {
    struct Let *ret = (struct Let *)malloc(sizeof(struct Let));

    ret -> id = strdup(id);
    ret -> val = val;
    ret -> type = 3;

    return ret;
}

struct Ref *new_ref(char* id) {
    struct Ref *ret = (struct Ref *)malloc(sizeof(struct Ref));

    ret -> id = strdup(id);
    ret -> type = 4;

    return ret;
}

char * prim_to_string(struct Prim *prim) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Prim(\"%s\", %s, %s)", prim->op, tree_to_string(prim->left), tree_to_string(prim->right));
    return ret;
}

char * lit_to_string(struct Lit *lit) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Lit(%d)", lit->val);
    return ret;
}

char * let_to_string(struct Let *let) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Let(%s, %s)", let->id, prim_to_string(let->val));
    return ret;
}

char * ref_to_string(struct Ref *ref) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Ref(%s)", ref->id);
    return ret;
}

char * tree_to_string(struct Tree *tree) {
    if (tree -> type == 1) {
        return prim_to_string((struct Prim *) tree);
    } else if (tree -> type == 2) {
        return lit_to_string((struct Lit *) tree);
    } else if (tree -> type == 3) {
        return let_to_string((struct Let *) tree);
    } else if (tree -> type == 4) {
        return ref_to_string((struct Ref *) tree);
    }
}

char * env_to_string(struct Env *env) {
    char * ret = (char *) malloc(2048);
    for (int i = 0; i < env->lines; i++) {
        char * idx = (char *) malloc(1024);
        sprintf(idx, "%s", tree_to_string(env->prog[i]));
        strcat(ret, idx);
        if (i < env->lines - 1) {
            strcat(ret, ", ");
        } else {
            strcat(ret, "\n");
        }
    }
    return ret;
}