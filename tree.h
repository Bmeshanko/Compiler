#include <vector>
#include <string>
#include <map>
#include <cstdlib>

struct Prim {
    char op;

    struct Prim *left;
    struct Prim *right;
};

struct Lit {
    int val;
};

struct Let {
    char * id;
    struct Prim * val;
};

struct Ref {
    char * id;
};

struct Prim *new_prim(char op, struct Prim *left, struct Prim *right);
struct Lit *new_lit(int val);

char * prim_to_string(struct Prim *tree);
char * let_to_string(struct Let *dec);
char * ref_to_string(struct Ref *ref);
