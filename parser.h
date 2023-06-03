#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#define N 1000

struct Tree {
    short type;
    struct Env *parent;
};

struct Env {
    struct Tree *prog[N]; // 0-indexed array representing each line of the program.
    int lines; // 1-indexed amount of lines in the program
};

struct Prim {
    short type;
    char* op;

    struct Tree *left;
    struct Tree *right;
};

struct Lit {
    short type;
    int val;
};

struct Let {
    short type;
    char* id;

    struct Tree *val;
};

struct Ref {
    short type;
    char* id;
};

struct If {
    short type;
    struct Tree *cond;
};

struct While {
    short type;
    struct Tree *cond;
};

struct End {
    short type;
};

struct Print {
    short type;
    struct Tree * val;
};

struct Env *new_env();
struct If *new_if(struct Tree *cond);
struct While *new_while(struct Tree *cond);
struct End *new_end();
struct Prim *new_prim(char* op, struct Tree *left, struct Tree *right);
struct Lit *new_lit(int val);
struct Let *new_let(char* id, struct Tree *val);
struct Ref *new_ref(char* id);
struct Print *new_print(struct Tree *ref);

char * tree_to_string(struct Tree *tree);
char * env_to_string(struct Env *env);
char * if_to_string(struct If *ifs);
char * while_to_string(struct While *whiles);
char * end_to_string(struct End *end);
char * prim_to_string(struct Prim *tree);
char * lit_to_string(struct Lit *lit);
char * let_to_string(struct Let *dec);
char * ref_to_string(struct Ref *ref);
char * print_to_string(struct Print *print);
