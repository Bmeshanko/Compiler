#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#define N 1000

struct Tree {
    short type;
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
    short element_type;
};

struct Array {
    short type;
    int element_type;
    std::string *id;
    struct Tree * size;
};

struct Let {
    short type;
    int element_type;
    std::string *id;
    struct Tree * index;
    struct Tree *val;

};

struct Ref {
    short type;
    std::string *id;
    struct Tree * index;
};

struct If {
    short type;
    struct Tree *cond;
};

struct While {
    short type;
    struct Tree *cond;
};

struct Fun {
    short type; // 9 - Void // 11 - Int
    std::string *id;
};

struct App {
    short type; // 10 - Void // 12 - Int
    std::string *id;
};

struct Return {
    short type;
    struct Tree *val;
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
struct Fun *new_fun(std::string *id, bool isVoid);
struct App *new_app(std::string *id, bool isVoid);
struct Return *new_return(struct Tree *val);
struct End *new_end();
struct Prim *new_prim(char* op, struct Tree *left, struct Tree *right);
struct Lit *new_lit(int val);
struct Let *new_let(std::string *id, struct Tree * index, struct Tree *val, int element_type);
struct Ref *new_ref(std::string *id, struct Tree * index);
struct Array *new_array(std::string *id, struct Tree * size, int element_type);
struct Print *new_print(struct Tree *ref);

int get_let_type(struct Let *let);
int get_array_type(struct Array *array);
void add_to_env(struct Env *env, struct Tree *tree);

char * tree_to_string(struct Tree *tree);
char * env_to_string(struct Env *env);
char * if_to_string(struct If *ifs);
char * while_to_string(struct While *whiles);
char * fun_to_string(struct Fun *fun, bool isVoid);
char * app_to_string(struct App *app, bool isVoid);
char * return_to_string(struct Return *returns);
char * end_to_string(struct End *end);
char * prim_to_string(struct Prim *tree);
char * lit_to_string(struct Lit *lit);
char * let_to_string(struct Let *dec);
char * ref_to_string(struct Ref *ref);
char * print_to_string(struct Print *print);
