#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

void eval(struct Env *prog) {
    
}

void evalGeneric(struct Tree *tree) {
    
}

void evalFromTo(struct Env *prog, int start, int end) {

}

void evalLet(struct Let *let) {

}

bool evalIf(struct If *ifs) {
    return evalPrim(ifs->cond) == 1;
}

bool evalWhile(struct While *whiles) {
    return evalPrim(whiles->cond) == 1;
}

int evalPrim(struct Prim *prim) {
    
}

int evalLit(struct Lit *lit) {
    return lit->val;
}

int evalRef(struct Ref *ref) {

}


