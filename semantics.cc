#include <bits/stdc++.h>
#include "semantics.hh"

struct TypedTree * new_typed_tree(struct Tree * tree, short force_type) {
    return NULL;
}

struct TypedPrim * new_typed_prim(struct Prim * prim) {
    struct TypedPrim * ret = (struct TypedPrim *)malloc(sizeof(struct TypedPrim));

    char * op = prim -> op;

    if (strcmp(op, "+") == 0) ret -> element_type = IntType;
    else if (strcmp(op, "-") == 0) ret -> element_type = IntType;
    else if (strcmp(op, "*")== 0) ret -> element_type = IntType;
    else if (strcmp(op, "/") == 0) ret -> element_type = IntType;
    else if (strcmp(op, "%") == 0) ret -> element_type = IntType;
    else if (strcmp(op, "^") == 0) ret -> element_type = IntType;
    else if (strcmp(op, "&") == 0) ret -> element_type = IntType;
    else if (strcmp(op, "|") == 0) ret -> element_type = IntType; 
    else if (strcmp(op, "<") == 0) ret -> element_type = BooleanType; 
    else if (strcmp(op, ">") == 0) ret -> element_type = BooleanType; 
    else if (strcmp(op, "==") == 0) ret -> element_type = BooleanType;  
    else if (strcmp(op, "!=") == 0) ret -> element_type = BooleanType; 
    else if (strcmp(op, "<=") == 0) ret -> element_type = BooleanType; 
    else if (strcmp(op, ">=") == 0) ret -> element_type = BooleanType; 
    else if (strcmp(op, "&&") == 0) ret -> element_type = BooleanType; 
    else if (strcmp(op, "||") == 0) ret -> element_type = BooleanType; 

    ret -> op = op;
    ret -> tree_type = 1;

    short force_type;

    // If we forced a type here, 'a' + 1 would be an error, not 'b'.
    ret -> left = new_typed_tree(prim -> left, -1);
    ret -> right = new_typed_tree(prim -> right, -1);

    return ret;
}

struct TypedLit * new_typed_lit(struct Lit * lit) {
    struct TypedLit * ret = (struct TypedLit *)malloc(sizeof(struct TypedLit));

    return ret;
}

struct TypedLet * new_typed_let(struct Let * let) {
    struct TypedLet * ret = (struct TypedLet *)malloc(sizeof(struct TypedLet));

    if (let -> element_type == 0) {
        ret -> element_type = IntType;
    } else if (let -> element_type == 1) {
        ret -> element_type = CharType;
    }

    ret -> id = let -> id;
    ret -> index = new_typed_tree(let -> index, 0); // Index must be IntType
    ret -> val = new_typed_tree(let -> val, -1); // Val can be any type
    ret -> tree_type = 3;

    return ret;
}

struct TypedRef * new_typed_ref(struct Ref * ref) {
    struct TypedRef * ret = (struct TypedRef *)malloc(sizeof(struct TypedRef));

    if (ref -> element_type == 0) {
        ret -> element_type = IntType;
    } else if (ref -> element_type == 1) {
        ret -> element_type = CharType;
    }

    ret -> id = ref -> id;
    ret -> index = new_typed_tree(ref -> index, 0);
    ret -> tree_type = 4;

    return ret;
}

struct TypedArrayDec * new_typed_arraydec(struct Array * array) {
    struct TypedArrayDec * ret = (struct TypedArrayDec *)malloc(sizeof(struct TypedArrayDec));

    if (array -> element_type == 0) {
        ret -> element_type = IntType;
    } else if (array -> element_type == 1) {
        ret -> element_type = CharType;
    }

    ret -> id = array -> id;
    ret -> size = new_typed_tree(array -> size, 0);
    ret -> tree_type = 14;

    return ret;
}

struct TypedIf * new_typed_if(struct If *ifs) {
    struct TypedIf * ret = (struct TypedIf *)malloc(sizeof(struct TypedIf));

    ret -> element_type = UnitType;
    ret -> cond = new_typed_tree(ifs -> cond, 2);
    ret -> tree_type = 5;

    return ret;
}

struct TypedWhile * new_typed_while(struct While *whiles) {
    struct TypedWhile * ret = (struct TypedWhile *)malloc(sizeof(struct TypedWhile));

    ret -> element_type = UnitType;
    ret -> cond = new_typed_tree(whiles -> cond, 2);
    ret -> tree_type = 5;

    return ret;
}

struct TypedReturn * new_typed_return(struct Return *returns) {
    struct TypedReturn * ret = (struct TypedReturn *)malloc(sizeof(struct TypedReturn));

    ret -> element_type = UnitType;
    ret -> val = new_typed_tree(returns -> val, -1);
    ret -> tree_type = 13;

    return ret;
}

struct TypedEnd * new_typed_end(struct End *end) {
    struct TypedEnd * ret = (struct TypedEnd *)malloc(sizeof(struct TypedEnd));

    ret -> element_type = UnitType;
    ret -> tree_type = 7;

    return ret;
}

