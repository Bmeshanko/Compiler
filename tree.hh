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

class Prim : Tree {
    char op;
    std::vector<Tree> args;
};

class Lit : Tree {
    int value;
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
