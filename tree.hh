#include <vector>
#include <string>
#include <map>

class Tree {
    public:
        Tree() {

        }
};

class AST {
    std::vector<Tree> nodes;
    public:
        AST() {
            
        }
};

class Prim : public Tree {
    char op;
    Tree arg1;
    Tree arg2;
    public:
        Prim(char op, Tree arg1, Tree arg2) {
            this -> op = op;
            this -> arg1 = arg1;
            this -> arg2 = arg2;
        }
};

class Lit : public Tree {
    int value;
    public:
        Lit(int value) {
            this -> value = value;
        }
};

class Let : Tree {
    std::string name;
    Tree value;
};

class Ref : Tree {
    std::string name;
};

class Env {
    std::map<std::string, int> vars;

    bool isDefined(std::string name) {
        return vars.count(name) > 0;
    }

    int getVar(std::string name) {
        return vars[name];
    }
    
    void varDec(std::string name, int value) {
        if (isDefined(name)) {
            fprintf(stderr, "Error: Variable %s is already defined.\n", name.c_str());
        } else {
            vars[name] = value;
        }
    }

    void varAssign(std::string name, int value) {
        if (!isDefined(name)) {
            fprintf(stderr, "Error: Variable %s is undefined.\n", name.c_str());
        } else {
            vars[name] = value;
        }
    }
};
