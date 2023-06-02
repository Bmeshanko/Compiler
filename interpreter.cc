#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "interpreter.h"

map<char *, int> variables;

void eval(struct Env *prog) {
    
}

void evalGeneric(struct Tree *tree) {

}

void evalFromTo(struct Env *prog, int start, int end) {

}

void evalLet(struct Let *let) {
     variables[let->id] = evalNum(let->val);
}

bool evalCond(struct Tree *tree) {
    if (tree -> type == 5) {
        return evalNum((struct If *) tree -> cond) == 0;
    } else if (tree -> type == 6) {
        return evalNum((struct While *) tree -> cond) == 0;
    } else {
        return NULL;
    }
}

int evalNum(struct Tree *tree) {
    if (tree -> type == 4) {
        return variables[(struct Ref *) tree -> id];
    } else if (tree -> type == 2) {
        return (struct Lit *) tree -> val;
    } else if (tree -> type == 1) {
        struct Prim * l = (struct Prim *) tree -> left;
        struct Prim * r = (struct Prim *) tree - > right;

        switch ((struct Prim *) tree -> op) {
            case "+": return evalPrim(l) + evalPrim(r);
            case "-": return evalPrim(l) - evalPrim(r);
            case "*": return evalPrim(l) * evalPrim(r);
            case "/": return evalPrim(l) / evalPrim(r);
            case "%%": return evalPrim(l) % evalPrim(r);
            case "|": return evalPrim(l) | evalPrim(r);
            case "&": return evalPrim(l) & evalPrim(r);
            case "^": return evalPrim(l) ^ evalPrim(r);
            case "==": return evalPrim(l) == evalPrim(r);
            case "!=": return evalPrim(l) != evalPrim(r);
            case "<=": return evalPrim(l) <= evalPrim(r);
            case ">=": return evalPrim(l) >= evalPrim(r);
            case "<": return evalPrim(l) < evalPrim(r);
            case ">": return evalPrim(l) > evalPrim(r);
        }
    } else {
        return NULL;
    }
}


