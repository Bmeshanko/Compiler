#include <bits/stdc++.h>
#include "semantics.hh"

struct TypedTree * new_typed_tree(struct Tree * tree, short force_type) {
    return NULL;
}

struct TypedPrim * new_typed_prim(struct Prim * prim, short force_type) {
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

char * ttree_string(struct TypedTree * tree) {

}

char * tprim_string(struct TypedPrim * prim) {

}

char * tlit_string(struct TypedLit * lit) {
    char * ret = (char *)malloc(1024);

    if (lit -> element_type == IntType) {
        sprintf(ret, "IntLit(%d)", lit -> val);
    } else if (lit -> element_type == CharType) {
        sprintf(ret, "CharLit(%c)", lit -> val);
    } else if (lit -> element_type == BooleanType) {
        if (lit -> val) sprintf(ret, "Lit(true)", lit -> val);
        else sprintf(ret, "Lit(false)", lit -> val);
    }

    return ret;
}

char * tlet_string(struct TypedLet * let) {
    char * ret = (char *)malloc(1024);
    sprintf(ret, "Let(%s, %s, %s, %s)", let->id->c_str(), let->element_type, ttree_to_string(let->index), ttree_to_string(let->val));
    return ret;
}

char * tref_string(struct TypedRef * ref) {
    char * ret = (char *)malloc(1024);
    sprintf(ret, "Ref(%s, %s, %s, %s)", ref->id->c_str(), ref->element_type, ttree_to_string(ref->index));
    return ret;
}

char * tarraydec_string(struct TypedArrayDec * array) {
    char * ret = (char *)malloc(1024);
    sprintf(ret, "ArrayDec(%s, %s, %s)", array->id->c_str(), array->element_type, ttree_string(array->size));
    return ret;
}

char * tif_string(struct TypedIf * ifs) {
    return if_to_string((struct If *) ifs);
}

char * twhile_string(struct TypedWhile * whiles) {
    return while_to_string((struct If *) ifs);
}

char * tfunc_string(struct TypedFunc * func);

char * tapp_string(struct TypedApp * app);

char * treturn_string(struct TypedReturn * returns);

char * tend_string(struct TypedEnd * end) {
    return end_to_string((struct End *) end);
}

char * tprint_string(struct TypedPrint * print) {
    char * ret = (char *)malloc(1024);
    sprintf(ret, "Print(%s, %s)", print->element_type, ttree_string(print->val));
    return ret;
}
