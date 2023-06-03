#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include "interpreter.hh"
#include "parser.hh"
#include <map>

typedef std::map<std::string, int> mci;

void eval(struct Env *prog, int start, int finish, mci &variables) {
    for (int i = start; i < finish; i++) {
        struct Tree * tree = prog->prog[i];
        short type = tree->type;

        if (type == 3) {
            // Let Statement
            evalLet((struct Let *) tree, variables);
        } else if (type == 5) {
            // If Statement
            int end = findEnd(prog, i);
            if (evalCond(((struct If *)tree)->cond, 5, variables)) {
                eval(prog, i + 1, end, variables);
            }
            i = end;
        } else if (type == 6) {
            // While Statement
            int end = findEnd(prog, i);
            while (evalCond(((struct While *)tree)->cond, 6, variables)) {
                eval(prog, i + 1, end, variables);
            }
            i = end;
        } else if (type == 8) {
            // Print Statement
            printf("%d\n", evalNum(((struct Print *)tree)->val, variables));
        } else {
            // End: Do nothing
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

void evalLet(struct Let *let, mci &variables) {
    variables.insert_or_assign(*(let -> id), evalNum(let -> val, variables));
}

bool evalCond(struct Tree *tree, int type, mci &variables) {
    return evalNum(tree, variables) != 0;
}

int evalNum(struct Tree *tree, mci &variables) {
    if (tree -> type == 4) {
        return variables[*(((struct Ref *) tree) -> id)];
    } else if (tree -> type == 2) {
        return ((struct Lit *) tree) -> val;
    } else if (tree -> type == 1) {
        struct Tree * l = ((struct Prim *) tree) -> left;
        struct Tree * r = ((struct Prim *) tree) -> right;

        char * op = ((struct Prim *) tree) -> op;

        if (strcmp(op, "+") == 0) return evalNum(l, variables) + evalNum(r, variables); 
        else if (strcmp(op, "-") == 0) return evalNum(l, variables) - evalNum(r, variables); 
        else if (strcmp(op, "*")== 0) return evalNum(l, variables) * evalNum(r, variables); 
        else if (strcmp(op, "/") == 0) return evalNum(l, variables) / evalNum(r, variables); 
        else if (strcmp(op, "%") == 0) return evalNum(l, variables) % evalNum(r, variables); 
        else if (strcmp(op, "^") == 0) return evalNum(l, variables) ^ evalNum(r, variables); 
        else if (strcmp(op, "&") == 0) return evalNum(l, variables) & evalNum(r, variables); 
        else if (strcmp(op, "|") == 0) return evalNum(l, variables) | evalNum(r, variables); 
        else if (strcmp(op, "<") == 0) return evalNum(l, variables) < evalNum(r, variables); 
        else if (strcmp(op, ">") == 0) return evalNum(l, variables) > evalNum(r, variables); 
        else if (strcmp(op, "==") == 0) return evalNum(l, variables) == evalNum(r, variables); 
        else if (strcmp(op, "!=") == 0) return evalNum(l, variables) != evalNum(r, variables); 
        else if (strcmp(op, "<=") == 0) return evalNum(l, variables) <= evalNum(r, variables); 
        else if (strcmp(op, ">=") == 0) return evalNum(l, variables) >= evalNum(r, variables);
        else if (strcmp(op, "&&") == 0) return evalNum(l, variables) && evalNum(r, variables);
        else if (strcmp(op, "||") == 0) return evalNum(l, variables) || evalNum(r, variables);
        else return 0;
    }
    return 0;
}


