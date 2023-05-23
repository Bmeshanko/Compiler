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

struct Prim *new_lit(int val) {
    struct Lit *ret = (struct Lit *)malloc(sizeof(struct Lit));

    ret -> val = val;

    return (struct Prim *) ret;
}

char * to_string(struct Prim *tree) {
    char * ret = (char *) malloc(1024);
    if (tree->left == NULL && tree->right == NULL) {
        struct Lit * leaf = (struct Lit *) tree;
        sprintf(ret, "Lit(%d)", leaf->val);
    } else {
        sprintf(ret, "Prim(\"%c\", %s, %s)", tree->op, to_string(tree->left), to_string(tree->right));
    }
    return ret;
}
