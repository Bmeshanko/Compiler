#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct Prim *new_prim(char *op, struct Prim *left, struct Prim *right) {
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

char * prim_to_string(struct Prim *tree) {
    char * ret = (char *) malloc(1024);
    if (tree->type == 2) {
        struct Lit *lit = (struct Lit *) tree;
        return lit_to_string(lit);
    } else if (tree->type == 4) {
        struct Ref *ref = (struct Ref *) tree;
        return ref_to_string(ref);
    } else if (tree->type == 1) {
        sprintf(ret, "Prim(\"%s\", %s, %s)", tree->op, prim_to_string(tree->left), prim_to_string(tree->right));
    }
    return ret;
}

char * lit_to_string(struct Lit *lit) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Lit(%d)", lit->val);
    return ret;
}

char * let_to_string(struct Let *dec) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Let(%s, %s)", dec->id, prim_to_string(dec->val));
    return ret;
}

char * ref_to_string(struct Ref *ref) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Ref(%s)", ref->id);
    return ret;
}
