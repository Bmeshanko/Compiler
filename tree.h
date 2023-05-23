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

struct Prim *new_prim(char op, struct Prim *left, struct Prim *right);
struct Prim *new_lit(int val);
char * to_string(struct Prim *tree);
