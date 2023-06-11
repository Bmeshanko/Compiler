#include "parser.hh"
#include <bits/stdc++.h>
using namespace std;

#define N 1000

class Type {
    std::string type;
    public:
        Type(std::string type) {
            this.type = type;
        }

        std::string toString() {
            return type;
        }
};

Type IntType = Type("Int");
Type CharType = Type("Char");
Type UnitType = Type("Unit"); // i.e. a Variable Declaration/If Statement is UnitType.
Type BooleanType = Type("Boolean");

class FunType : Type {
    vector<pair<std::string, Type>> args;

    public:
        Type(vector<pair<std::string, Type>> args) {
            this.args = args;
        }

        std::string toString() {
            std::string ret = "(";
            for (auto arg : args) {
                ret += "[" + arg.first() + ", " + arg.second + "]";
            }
            ret += ")";
            return ret;
        }
};

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
    // We will still use 64-bit long for a boolean. This will waste memory in the intermediate phases,
    // but the resultant ASM program will be unaffected by this decision. 
    // Unit is always 0, Char will be 0-256, and Boolean is always 0 or 1.
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
    struct Tree * index;
    short tree_type;
};

struct TypedIf {
    Type element_type;
    struct Tree * cond;
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

Type typeInfer(struct Tree * tree);
void analyzeSemantics(struct Env * prog);