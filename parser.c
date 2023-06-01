#include <stdlib.h>
#include <string.h>
#include "parser.h"

/*
*   Constructor Functions
*/

struct Env *new_env() {
    struct Env *ret = (struct Env *)malloc(sizeof(struct Env));

    ret -> lines = 0;

    return ret;
}

struct If *new_if(struct Tree *cond) {
    struct If *ret = (struct If *)malloc(sizeof(struct If));

    ret -> cond = cond;
    ret -> type = 5;

    return ret;
}

struct While *new_while(struct Tree *cond) {
    struct While *ret = (struct While *)malloc(sizeof(struct While));

    ret -> cond = cond;
    ret -> type = 6;

    return ret;
}

struct End *new_end() {
    struct End *ret = (struct End *)malloc(sizeof(struct End));

    ret -> type = 7;

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

struct Let *new_let(char* id, struct Tree *val) {
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

struct Print * new_print(struct Tree* ref) {
    struct Print *ret = (struct Print *)malloc(sizeof(struct Print));

    ret -> ref = ref;
    ret -> type = 8;

    return ret;
}

/*
*   Add To Environment Function
*/

void add_to_env(struct Env *env, struct Tree *tree) {
    env->prog[env->lines++] = tree;
}

/*
*   To String Functions
*/

char * env_to_string(struct Env *env) {
    char * ret = (char *) malloc(2048);
    for (int i = 0; i < env->lines; i++) {
        char * idx = (char *) malloc(1024);
        sprintf(idx, "%s", tree_to_string(env->prog[i]));
        strcat(ret, idx);
        if (i < env->lines - 1) {
            strcat(ret, ";\n");
        } else {
            strcat(ret, "\n");
        }
    }
    return ret;
}

// You cannot name a variable "if"
char * if_to_string(struct If *ifs) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "If(%s)", tree_to_string(ifs->cond));
    return ret;
}

// You cannot name a variable "while"
char * while_to_string(struct While *whiles) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "While(%s)", tree_to_string(whiles->cond));
    return ret;
}

char * end_to_string(struct End *end) {
    char * ret = (char *) malloc(16);
    sprintf(ret, "End");
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
    sprintf(ret, "Let(%s, %s)", let->id, tree_to_string(let->val));
    return ret;
}

char * ref_to_string(struct Ref *ref) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Ref(%s)", ref->id);
    return ret;
}

char * print_to_string(struct Print *print) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Print(%s)", tree_to_string(print->ref));
    return ret;
}

char * tree_to_string(struct Tree *tree) {
    switch (tree -> type) {
        case 1:
            return prim_to_string((struct Prim *) tree);
        case 2:
            return lit_to_string((struct Lit *) tree);
        case 3:
            return let_to_string((struct Let *) tree);
        case 4:
            return ref_to_string((struct Ref *) tree);
        case 5:
            return if_to_string((struct If*) tree);
        case 6:
            return while_to_string((struct While*) tree);
        case 7:
            return end_to_string((struct End*) tree);
        case 8:
            return print_to_string((struct Print*) tree);
    }
    return NULL;
}