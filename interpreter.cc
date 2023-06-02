#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "interpreter.h"

map<char *, int> variables;

void eval(struct Env *prog, int start, int end) {
    for (int i = start; i < end; i++) {
        struct Tree * tree = prog->prog[i];
        short type = tree->type;

        if (type == 3) {
            // Let Statement
            evalLet((struct Let *) tree);
        } else if (type == 5) {
            // If Statement
            int end = findEnd(prog, i);
            if (evalCond((struct If *)tree->cond), 5) {
                eval(prog, i + 1, end);
            }
        } else if (type == 6) {
            // While Statement
            int end = findEnd(prog, i);
            while (evalCond((struct While *)tree->cond), 6) {
                eval(prog, i + 1, end);
            }
        } else if (type == 8) {
            // Print Statement
        } else {
            // Do nothing
        }
    }
}

int findEnd(struct Env *prog, int start) {
    int diff = 1;
    for (int i = start + 1; i < prog->lines; i++) {
        short type = prog->prog[i]->type;
        if (type == 7) diff--;
        if (type == 4 || type == 5) diff++;
        if (diff == 0) return i;
    }
    return -1;
}

void evalLet(struct Let *let) {
     variables[let->id] = evalNum(let->val);
}

bool evalCond(struct Tree *tree, short type) {
    if (type == 5) {
        return evalNum((struct If *) tree -> cond) == 0;
    } else if (type == 6) {
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


