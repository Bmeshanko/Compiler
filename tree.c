#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include "tree.h"

struct Prim *new_prim(char op, struct Prim *left, struct Prim *right) {
    struct Prim *ret = (struct Prim *)malloc(sizeof(struct Prim));

    ret -> op = op;
    ret -> left = left;
    ret -> right = right;

    return ret;
}

struct Lit *new_lit(int val) {
    struct Lit *ret = (struct Lit *)malloc(sizeof(struct Lit));

    ret -> val = val;

    return ret;
}

struct Let *new_let(char* id, struct Prim *val) {
    struct Let *ret = (struct Let *)malloc(sizeof(struct Let));

    ret -> id = id;
    ret -> val = val;
    
    return ret;
}

struct Ref *new_ref(char* id) {
    struct Ref *ret = (struct Ref *)malloc(sizeof(struct Ref));

    ret -> id = id;

    return ret;
}

char * prim_to_string(struct Prim *tree) {
    char * ret = (char *) malloc(1024);
    if (tree->left == NULL && tree->right == NULL) {
        struct Lit * leaf = (struct Lit *) tree;
        sprintf(ret, "Lit(%d)", leaf->val);
    } else {
        sprintf(ret, "Prim(\"%c\", %s, %s)", tree->op, prim_to_string(tree->left), prim_to_string(tree->right));
    }
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
