#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include "interpreter.hh"
#include "parser.hh"
#include <map>

typedef std::map<std::string, int *> mci;

void eval(struct Env *prog, int start, int finish, mci &variables) {
    for (int i = start; i < finish; i++) {
        struct Tree * tree = prog->prog[i];
        short type = tree->type;

        if (type == 3) {
            // Let Statement
            evalLet(prog, (struct Let *) tree, variables);
        } else if (type == 5) {
            // If Statement
            int end = findEnd(prog, i);
            if (evalCond(prog, ((struct If *)tree)->cond, 5, variables)) {
                eval(prog, i + 1, end, variables);
            }
            i = end;
        } else if (type == 6) {
            // While Statement
            int end = findEnd(prog, i);
            while (evalCond(prog, ((struct While *)tree)->cond, 6, variables)) {
                eval(prog, i + 1, end, variables);
            }
            i = end;
        } else if (type == 8) {
            // Print Statement
            printf("%d\n", evalNum(prog, ((struct Print *)tree)->val, variables));
        } else if (type == 9 || type == 11) {
            // Function Def Statement
            int end = findEnd(prog, i);
            // Insert the function name and the start location.
            variables.insert({*((struct Fun *)tree)->id, &i});
            i = end;
        } else if (type == 10) {
            // Void Function application.
            int funStart = *variables[*((struct App *)tree)->id] + 1;
            int funEnd = findEnd(prog, funStart);
            // Find start and end, execute.
            eval(prog, funStart, funEnd, variables);
        } else {
            // Int Functions cannot be evaluated on their own.
            // NOP
        }
    }
}

int findEnd(struct Env *prog, int start) {
    int diff = 1;
    for (int i = start + 1; i < prog->lines; i++) {
        short type = prog->prog[i]->type;
        if (type == 7) diff--;
        if (type == 5 || type == 6 || type == 9 || type == 11) diff++;
        if (diff == 0) return i;
    }
    return -1;
}

int evalFun(struct Env *prog, int start, mci &variables) {

    int finish = findEnd(prog, start);
    // Same as standard eval() but returns will return the value
    for (int i = start; i < finish; i++) {
        struct Tree * tree = prog->prog[i];
        short type = tree->type;

        if (type == 3) {
            // Let Statement
            evalLet(prog, (struct Let *) tree, variables);
        } else if (type == 5) {
            // If Statement
            int end = findEnd(prog, i);
            if (evalCond(prog, ((struct If *)tree)->cond, 5, variables)) {
                evalFun(prog, i + 1, variables);
            }
            i = end;
        } else if (type == 6) {
            // While Statement
            int end = findEnd(prog, i);
            while (evalCond(prog, ((struct While *)tree)->cond, 6, variables)) {
                evalFun(prog, i + 1, variables);
            }
            i = end;
        } else if (type == 8) {
            // Print Statement
            printf("%d\n", evalNum(prog, ((struct Print *)tree)->val, variables));
        } else if (type == 10) {
            // Function application.
            int funStart = *(variables[*((struct App *)tree)->id]) + 1;
            int funEnd = findEnd(prog, funStart);
            // Find start and end, execute.
            eval(prog, funStart, funEnd, variables);
        } else if (type == 13) {
            // Function Return
            return evalNum(prog, ((struct Return *) tree)->val, variables);
        } else {
            // NOP
        }
    }
    return -1;
}

void evalLet(struct Env *prog, struct Let *let, mci &variables) {
    if (variables.count(*(let -> id)) != 0) {
        int * arr = variables[*(let -> id)];
        arr[evalNum(prog, let -> index, variables)] = evalNum(prog, let -> val, variables);
        variables[*(let -> id)] = arr;
    } else {
        // Let is defining a new variable, we need to create a new int[1].
        // Otherwise, this would've been parsed by Array and is a different case.
        int arr[1];
        arr[0] = evalNum(prog, let -> val, variables);
        variables[*(let -> id)] = arr;
    }
}

bool evalCond(struct Env *prog, struct Tree *tree, int type, mci &variables) {
    return evalNum(prog, tree, variables) != 0;
}

int evalNum(struct Env *prog, struct Tree *tree, mci &variables) {
    if (tree -> type == 12) {
        return evalFun(prog, *variables[*(((struct App *) tree) -> id)], variables);
    } else if (tree -> type == 4) {
        return variables[*(((struct Ref *) tree) -> id)][evalNum(prog, ((struct Ref *) tree) -> index, variables)];
    } else if (tree -> type == 2) {
        return ((struct Lit *) tree) -> val;
    } else if (tree -> type == 1) {
        struct Tree * l = ((struct Prim *) tree) -> left;
        struct Tree * r = ((struct Prim *) tree) -> right;

        char * op = ((struct Prim *) tree) -> op;

        if (strcmp(op, "+") == 0) return evalNum(prog, l, variables) + evalNum(prog, r, variables); 
        else if (strcmp(op, "-") == 0) return evalNum(prog, l, variables) - evalNum(prog, r, variables); 
        else if (strcmp(op, "*")== 0) return evalNum(prog, l, variables) * evalNum(prog, r, variables); 
        else if (strcmp(op, "/") == 0) return evalNum(prog, l, variables) / evalNum(prog, r, variables); 
        else if (strcmp(op, "%") == 0) return evalNum(prog, l, variables) % evalNum(prog, r, variables); 
        else if (strcmp(op, "^") == 0) return evalNum(prog, l, variables) ^ evalNum(prog, r, variables); 
        else if (strcmp(op, "&") == 0) return evalNum(prog, l, variables) & evalNum(prog, r, variables); 
        else if (strcmp(op, "|") == 0) return evalNum(prog, l, variables) | evalNum(prog, r, variables); 
        else if (strcmp(op, "<") == 0) return evalNum(prog, l, variables) < evalNum(prog, r, variables); 
        else if (strcmp(op, ">") == 0) return evalNum(prog, l, variables) > evalNum(prog, r, variables); 
        else if (strcmp(op, "==") == 0) return evalNum(prog, l, variables) == evalNum(prog, r, variables); 
        else if (strcmp(op, "!=") == 0) return evalNum(prog, l, variables) != evalNum(prog, r, variables); 
        else if (strcmp(op, "<=") == 0) return evalNum(prog, l, variables) <= evalNum(prog, r, variables); 
        else if (strcmp(op, ">=") == 0) return evalNum(prog, l, variables) >= evalNum(prog, r, variables);
        else if (strcmp(op, "&&") == 0) return evalNum(prog, l, variables) && evalNum(prog, r, variables);
        else if (strcmp(op, "||") == 0) return evalNum(prog, l, variables) || evalNum(prog, r, variables);
        else return 0;
    }
    return 0;
}


