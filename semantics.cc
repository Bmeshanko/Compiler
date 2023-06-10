#include <bits/stdc++.h>
#include "semantics.hh"
#include "parser.hh"

struct TypedPrim * new_typed_prim(struct Prim * prim) {
    struct TypedPrim * ret = malloc(sizeof(struct TypedPrim));

    char * op = prim -> op;
    
    Type type;
    if (strcmp(op, "+") == 0) type = IntType;
    else if (strcmp(op, "-") == 0) type = IntType;
    else if (strcmp(op, "*")== 0) type = IntType;
    else if (strcmp(op, "/") == 0) type = IntType;
    else if (strcmp(op, "%") == 0) type = IntType;
    else if (strcmp(op, "^") == 0) type = IntType;
    else if (strcmp(op, "&") == 0) type = IntType;
    else if (strcmp(op, "|") == 0) type = IntType; 
    else if (strcmp(op, "<") == 0) type = BooleanType; 
    else if (strcmp(op, ">") == 0) type = BooleanType; 
    else if (strcmp(op, "==") == 0) type = BooleanType;  
    else if (strcmp(op, "!=") == 0) type = BooleanType; 
    else if (strcmp(op, "<=") == 0) type = BooleanType; 
    else if (strcmp(op, ">=") == 0) type = BooleanType; 
    else if (strcmp(op, "&&") == 0) type = BooleanType; 
    else if (strcmp(op, "||") == 0) type = BooleanType; 

    ret -> element_type = type;
    ret -> op = op;
    ret -> tree_type = 1;

    short force_type;

    // If we forced a type here, 'a' + 1 would be an error, not 'b'.
    ret -> left = new_typed_tree(prim -> left, -1);
    ret -> right = new_typed_tree(prim -> right, -1);

    return ret;
}

struct TypedLet * new_typed_let(struct Let * let) {
    struct TypedLet * ret = malloc(sizeof(struct TypedLet));

    Type type;
    if (let -> element_type == 0) {
        type = IntType;
    } else if (let -> element_type == 1) {
        type = CharType;
    }

    ret -> id = let -> id;
    ret -> index = new_typed_tree(let -> index, 0); // Index must be IntType
    ret -> val = new_typed_tree(let -> val, -1); // Val can be any type
    ret -> tree_type = 3;

    return ret;
}