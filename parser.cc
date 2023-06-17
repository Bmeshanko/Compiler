#include <stdlib.h>
#include <string>
#include <cstring>
#include "parser.hh"

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

struct Fun *new_fun(std::string *id, bool isVoid) {
    struct Fun *ret = (struct Fun *)malloc(sizeof(struct Fun));

    ret -> id = id;
    if (isVoid) ret -> type = 9;
    else ret -> type = 11;

    return ret;
}

struct App *new_app(std::string *id, bool isVoid) {
    struct App *ret = (struct App *)malloc(sizeof(struct App));

    ret -> id = id;
    if (isVoid) ret -> type = 10;
    else ret -> type = 12;

    return ret;
}

struct Return *new_return(struct Tree *val) {
    struct Return *ret = (struct Return *)malloc(sizeof(struct Return));

    ret -> val = val;
    ret -> type = 13;

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

struct Let *new_let(std::string *id, struct Tree * index, struct Tree *val, short element_type) {
    struct Let *ret = (struct Let *)malloc(sizeof(struct Let));

    ret -> id = id;
    ret -> index = index;
    ret -> val = val;
    ret -> type = 3;
    ret -> element_type = element_type;

    return ret;
}

struct Ref *new_ref(std::string *id, struct Tree * index) {
    struct Ref *ret = (struct Ref *)malloc(sizeof(struct Ref));

    ret -> id = id;
    ret -> index = index;
    ret -> type = 4;

    return ret;
}

struct Array *new_array(std::string *id, struct Tree * size, int element_type) {
    struct Array *ret = (struct Array *)malloc(sizeof(struct Array));

    ret -> id = id;
    ret -> size = size;
    ret -> type = 14;
    ret -> element_type = element_type;

    return ret;
}

struct Print * new_print(struct Tree* val) {
    struct Print *ret = (struct Print *)malloc(sizeof(struct Print));

    ret -> val = val;
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
*   Element Type Getters
*/

int get_let_type(struct Let *let) {
    return let -> element_type;
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

char * fun_to_string(struct Fun *fun) {
    char * ret = (char *) malloc(1024);
    if (fun -> type == 9) {
        sprintf(ret, "VoidDef(%s)", fun->id->c_str());
    } else {
        sprintf(ret, "IntDef(%s)", fun->id->c_str());
    }
    return ret;
}

char * app_to_string(struct App *app) {
    char * ret = (char *) malloc(1024);
    if (app -> type == 10) {
        sprintf(ret, "VoidApp(%s)", app->id->c_str());
    } else {
        sprintf(ret, "IntApp(%s)", app->id->c_str());
    }
    return ret;
}

char * return_to_string(struct Return *returns) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Return(%s)", tree_to_string(returns->val));
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
    sprintf(ret, "Let(%s, %s, %s)", let->id->c_str(), tree_to_string(let->index), tree_to_string(let->val));
    return ret;
}

char * ref_to_string(struct Ref *ref) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Ref(%s, %s)", ref->id->c_str(), tree_to_string(ref->index));
    return ret;
}

char * array_to_string(struct Array *array) {
    char * ret = (char *) malloc(1024);
    if (array -> element_type == 0) {
        sprintf(ret, "Array(Int, %s, %s)", array->id->c_str(), tree_to_string(array->size));
    } else if (array -> element_type == 1) {
        sprintf(ret, "Array(Char, %s, %s)", array->id->c_str(), tree_to_string(array->size));
    }
    return ret;
}

char * print_to_string(struct Print *print) {
    char * ret = (char *) malloc(1024);
    sprintf(ret, "Print(%s)", tree_to_string(print->val));
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
        case 9: case 11:
            return fun_to_string((struct Fun *) tree);
        case 10: case 12:
            return app_to_string((struct App *) tree);
        case 13: 
            return return_to_string((struct Return *) tree);
        case 14:
            return array_to_string((struct Array *) tree);
    }
    return NULL;
}