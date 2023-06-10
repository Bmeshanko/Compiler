#include <bits/stdc++.h>
#include "semantics.hh"
#include "parser.hh"

struct TypedPrim * new_typed_prim(struct Prim * prim) {
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

    struct TypedPrim * ret = malloc(sizeof(struct TypedPrim));

    ret -> element_type = type;
    ret -> op = op;
    ret -> tree_type = 1;
    ret -> left = new_typed_tree(prim -> left);
    ret -> right = new_typed_tree(prim -> right);

    return ret;
}