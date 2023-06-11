#include "parser.hh"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#define N 1000

class Type {
    std::string type;
    public:
        Type(std::string t) {
            type = t;
        }

        std::string toString() {
            return type;
        }
};


Type IntType = Type("Int");
Type CharType = Type("Char");
Type UnitType = Type("Unit"); // i.e. a Variable Declaration/If Statement is UnitType.
Type BooleanType = Type("Boolean");

struct TypedTree {
    Type element_type;
    short tree_type;
};

struct TypedEnv {
    struct TypedTree * prog[N];
    int lines;
};

struct TypedPrim {
    Type element_type;
    char * op;
    struct TypedTree * left;
    struct TypedTree * right;
    short tree_type;
};

struct TypedLit {
    Type element_type;
    long long int val;
    short tree_type;
};

struct TypedArrayDec {
    Type element_type;
    std::string * id;
    struct TypedTree * size;
    short tree_type;
};

struct TypedLet {
    Type element_type;
    std::string * id;
    struct TypedTree * index;
    struct TypedTree * val;
    short tree_type;
};

struct TypedRef {
    Type element_type;
    std::string * id;
    struct TypedTree * index;
    short tree_type;
};

struct TypedIf {
    Type element_type;
    struct TypedTree * cond;
    short tree_type;
};

struct TypedWhile {
    Type element_type;
    struct TypedTree * cond;
    short tree_type;
};

struct TypedFunc {
    Type element_type;
    std::string * id;
    short tree_type;
};

struct TypedApp {
    Type element_type;
    std::string * id;
    short tree_type;
};

struct TypedReturn {
    Type element_type;
    struct TypedTree * val;
    short tree_type;
};

struct TypedEnd {
    Type element_type;
    short tree_type;
};

struct TypedPrint {
    Type element_type;
    struct TypedTree * val;
    short tree_type;
};

struct TypedTree * new_typed_tree(struct Tree * tree, short force_type);
struct TypedPrim * new_typed_prim(struct Prim * prim);
struct TypedLit * new_typed_lit(struct Lit * lit);
struct TypedArrayDec * new_typed_arraydec(struct Array * array);
struct TypedLet * new_typed_let(struct Let * let);
struct TypedRef * new_typed_ref(struct Ref * ref);
struct TypedIf * new_typed_if(struct If * ifs);
struct TypedWhile * new_typed_while(struct While * whiles);
struct TypedFunc * new_typed_func(struct Fun * fun);
struct TypedApp * new_typed_app(struct App * app);
struct TypedReturn * new_typed_return(struct Return *returns);
struct TypedEnd * new_typed_end(struct End *end);
struct TypedPrint * new_typed_print(struct Print *print);

char * ttree_string(struct TypedTree * tree);
char * tprim_string(struct TypedPrim * prim);
char * tlit_string(struct TypedLit * lit);
char * tlet_string(struct TypedLet * let);
char * tref_string(struct TypedRef * ref);
char * tarraydec_string(struct TypedArrayDec * array);
char * tif_string(struct TypedIf * ifs);
char * twhile_string(struct TypedWhile * whiles);
char * tfunc_string(struct TypedFunc * func);
char * tapp_string(struct TypedApp * app);
char * treturn_string(struct TypedReturn * returns);
char * tend_string(struct TypedEnd * end);
char * tprint_string(struct TypedPrint * print);

Type typeInfer(struct Tree * tree);
void analyzeSemantics(struct Env * prog);