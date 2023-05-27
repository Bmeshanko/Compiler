#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#define N 1000

struct Tree {
    short type;
    struct Tree *next;
};

struct Prim {
    short type;
    char* op;

    struct Prim *left;
    struct Prim *right;
};

struct Lit {
    short type;
    int val;
};

struct Let {
    short type;
    char* id;

    struct Prim *val;
};

struct Ref {
    short type;
    char* id;
};

struct If {
    short type;
    struct Prim *cond;
    struct Body *body;
};

struct Env {
    struct Tree prog[N];
};

struct Prim *new_prim(char* op, struct Prim *left, struct Prim *right);
struct Lit *new_lit(int val);
struct Let *new_let(char* id, struct Prim *val);
struct Ref *new_ref(char* id);

char * prim_to_string(struct Prim *tree);
char * lit_to_string(struct Lit *lit);
char * let_to_string(struct Let *dec);
char * ref_to_string(struct Ref *ref);
